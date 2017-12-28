//Lynne Diep                                                                                                                                                                         
//lytdiep@ucsc.edu                                                                                                                                                                   
//CMPS 101                                                                                                                                                                           
//PA 3                                                                                                                                                                               
//Matrix.java                                                                                                                                                                        

public class Matrix {
    private class Entry{
        int column;
        double value;

        Entry(int column, double value){
            this.column = column;
            this.value = value;
        }

        public String toString() {//(1,2) format                                                                                                                                     
            return "(" + column + ", " + value + ")";
        }

        public boolean equals(Object x) {//template taken from handout                                                                                                               
            boolean eq = false;
            Entry that;
            if(x instanceof Entry) {
                that = (Entry) x;
                eq = (this.column == that.column && this.value == that.value);
            }
            return eq;
        }
    }

    List[] row;
    int size;
    int NNZ;

    Matrix(int n){
        if(n < 1){
            throw new RuntimeException("Matrix() called on negative column count");
        }
        row = new List[n+1];
        for(int i = 1; i < (n+1); i++){
            row[i] = new List();
        }
    }

    int getSize(){// Returns n, the number of rows and columns of this Matrix                                                                                                        
        return row.length - 1;
    }

    int getNNZ(){ // Returns the number of non-zero entries in this Matrix                                                                                                           
        int count = 0;
        for(int i = 1; i <= getSize(); i++) {
            count += row[i].length();
         }
        return count;
    }

    public boolean equals(Object x) {// overrides Object's equals() method                                                                                                           
        Matrix that;
        if(x instanceof Matrix) {
            that = (Matrix) x;
            if(getSize() != that.getSize()){
                return false;
            }
            for(int i = 1; i <= getSize(); ++i) {
                if(!(row[i].equals(that.row[i]))){
                    return false;
                }
            }
        }
        return true;
    }


    void makeZero(){// sets this Matrix to the zero state                                                                                                                            
        for(int i = 1; i <= getSize(); ++i) {
            row[i].clear();
        }
    }

Matrix copy(){// returns a new Matrix having the same entries as this Matrix                                                                                                     
        Matrix M = new Matrix(getSize());
        for(int i = 1; i <= getSize(); ++i) {
            row[i].moveFront();
            while(row[i].index() >= 0) {
                Entry temp = (Entry) row[i].get();
                M.changeEntry(i, temp.column, temp.value);
                row[i].moveNext();
            }
        }
        return M;
    }

    void changeEntry(int i, int j, double x){ // Pre: 1 <= i <= getSize(), 1 <= j <= getSize()                                                                                       
        if(i < 1 || getSize() < i){
            throw new RuntimeException("changeEntry() called on Matrix with invalid ith position");
        }
        if(j < 1 || getSize() < j){
            throw new RuntimeException("changeEntry() called on Matrix with invalid jth position");
        }
        boolean answer = false;
        row[i].moveFront();
        while(row[i].index() >= 0) {
            Entry entry = (Entry) row[i].get();
            answer = (entry.column == j ? true : false);
            if(answer) {
		if(x == 0.0) {
                row[i].delete();
                    return;
                } else {
                    entry.value = x;
                    return;
                }
            }
            row[i].moveNext();
        }
        if(x != 0.0 && !answer){
            row[i].moveFront();
            if(row[i].index() == -1) {
                row[i].append(new Entry(j, x));
                return;
            } else {
                while(row[i].index() > -1 && ((Entry)row[i].get()).column < j) {
                    row[i].moveNext();
                }
                if(row[i].index() > -1) {
                    row[i].insertBefore(new Entry(j, x));
                    return;
                } else {
                    row[i].append(new Entry(j, x));
                    return;
                }
            }
        }
    }

    Matrix scalarMult(double x) {// returns a new Matrix that is the scalar product of this Matrix with x                                                                            
        Matrix M = this.copy();
        for(int i = 1; i <= M.getSize(); ++i) {
            M.row[i].moveFront();
            while(M.row[i].index() >= 0) {
                Entry temp = (Entry) M.row[i].get();
                M.changeEntry(i, temp.column, (x * temp.value));
                M.row[i].moveNext();
            }
        }
        return M;
    }

    Matrix add(Matrix M){// returns a new Matrix that is the sum of this Matrix with M                                                                                               
        if(getSize() != M.getSize()){// pre: getSize()==M.getSize()                                                                                                                  
            throw new RuntimeException("add() did not call on equal matrix sizes");
        }
        if(M == this)
            return this.copy().scalarMult(2);
        Matrix A = new Matrix(getSize());
        for(int i = 1; i <= getSize(); ++i) {
            A.row[i] = addOrSub(row[i], M.row[i], true);
        }
        return A;
    }

    Matrix sub(Matrix M){// returns a new Matrix that is the difference of this Matrix with M                                                                                        
        if(getSize() != M.getSize()){// pre: getSize()==M.getSize()                                                                                                                  
            throw new RuntimeException("add() did not call on equal matrix sizes");
        }
        if(M == this) {
            return new Matrix(getSize());
        }
        Matrix A = new Matrix(getSize());
        for(int i = 1; i <= getSize(); ++i) {
            A.row[i] = addOrSub(row[i], M.row[i], false);
        }
        return A;
    }

    Matrix transpose() {// returns a new Matrix that is the transpose of this Matrix                                                                                                 
        Matrix M = new Matrix(getSize());
        for(int i = 1; i <= getSize(); ++i) {
            row[i].moveFront();
            while(row[i].index() >= 0) {
                M.changeEntry(((Entry)row[i].get()).column, i, ((Entry)row[i].get()).value);
                row[i].moveNext();
            }
        }
        return M;
    }

 Matrix mult(Matrix M) {// returns a new Matrix that is the product of this Matrix with M                                                                                         
        if(getSize() != M.getSize()){// pre: getSize()==M.getSize()                                                                                                                  
            throw new RuntimeException("mult() did not call on equal matrix sizes");
        }
        Matrix A = new Matrix(getSize());
        Matrix Matrix2 = M.transpose();
        for(int i = 1; i <= getSize(); ++i) {
            if(row[i].length() == 0){
                continue;
            }
            for(int j = 1; j <= getSize(); ++j) {
                if(Matrix2.row[j].length() == 0){
                    continue;
                }
                A.changeEntry(i, j, dot(row[i], Matrix2.row[j]));
            }
        }
        return A;
    }

    public String toString() {// overrides Object's toString() method                                                                                                                
        String out = "";
        for(int i = 1; i <= getSize(); ++i) {
            if(row[i].length() > 0)
                out += (i + ": " + row[i] + "\n");
        }
        return out;
}

    private List addOrSub(List A, List B, boolean plus) {// helper function to add or subtract matrix                                                                                
        List L = new List();
        A.moveFront();
        B.moveFront();
        while(A.index() >= 0 || B.index() >= 0){
            if(A.index() >= 0 && B.index() >= 0){
                Entry a = (Entry) A.get();
                Entry b = (Entry) B.get();
                if(a.column > b.column){
                    L.append(new Entry(b.column, (plus ? 1.0 : -1.0)*b.value));
                    B.moveNext();
                }
                else if (a.column < b.column){
                    L.append(new Entry(a.column,a.value));
                    A.moveNext();
                }
                else if (a.column == b.column){
                    if((plus==true &&( a.value + b.value) != 0) ||(plus==false && (a.value-b.value)!= 0)){
                        L.append(new Entry(a.column, (plus ? a.value + b.value : a.value-b.value)));
                    }
                    A.moveNext();
                    B.moveNext();
                }
            }
            else if(A.index() >= 0){
                Entry a = (Entry) A.get();
                L.append(new Entry(a.column,a.value));
                A.moveNext();
            }
            else{
                Entry b = (Entry) B.get();
                L.append(new Entry(b.column, b.value));
                B.moveNext();
            }
        }
        return L;
    }

    private static double dot(List A, List B){// helper function to do dot product of matrix                                                                                         
        double product = 0.0;
        A.moveFront();
        B.moveFront();
        while(A.index() >= 0 && B.index() >= 0){
            Entry a = (Entry) A.get();
            Entry b = (Entry) B.get();
            if(a.column > b.column){
                B.moveNext();
            }
            else if (a.column < b.column){
                A.moveNext();
            }
            else{
                 product = product + (a.value * b.value);
                A.moveNext();
                B.moveNext();
            }
        }
        return product;
    }
}//matches public class Matrix   
