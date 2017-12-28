//Lynne Diep                                                                                                                                                                         
//lytdiep@ucsc.edu                                                                                                                                                                   
//CMPS 101                                                                                                                                                                           
//PA3                                                                                                                                                                                
//Sparse.java                                                                                                                                                                        

import java.io.*;
import java.util.Scanner;

public class Sparse{ //taken from FileIO example in handout                                                                                                                          
    public static void main(String[] args) throws IOException{
        Scanner in = null;
	PrintWriter out = null;
        String line = null;
        String[] token = null;
	int i, lineNumber = 0;

        if(args.length < 2){//check if correct argument length                                                                                                                       
            System.err.println("Usage: Sparse  infile outfile");
            System.exit(1);
        }

        in = new Scanner(new File(args[0]));
        out = new PrintWriter(new FileWriter(args[1]));

        int line1, line2;
	line = in.nextLine()+" ";    // add extra space so split works right                                                                                                         
	token = line.split("\\s+");  // split line around white space                                                                                                                
	Matrix A = new Matrix(Integer.parseInt(token[0]));
	Matrix B = new Matrix(Integer.parseInt(token[0]));
	line1 = Integer.parseInt(token[1])+2;
	line2 = Integer.parseInt(token[2])+line1+1;

	in = new Scanner(new File(args[0]));
	out = new PrintWriter(new FileWriter(args[1]));

	while( in.hasNextLine() ){
            lineNumber++;
            line = in.nextLine()+" ";    // add extra space so split works right                                                                                                     
            token = line.split("\\s+");  // split line around white space                                                                                                            
            if(lineNumber > 2 && lineNumber <= line1){
		A.changeEntry(Integer.parseInt(token[0]), Integer.parseInt(token[1]), Double.parseDouble(token[2]));
            }
            if(lineNumber > (line1 + 1) && lineNumber <= line2) {
		B.changeEntry(Integer.parseInt(token[0]), Integer.parseInt(token[1]), Double.parseDouble(token[2]));
            }
	}

        //Format taken from PA3 handout                                                                                                                                              

	System.out.println("A has " + A.getNNZ() + " non-zero entries");
	System.out.println(A);

 System.out.println("B has " + B.getNNZ() + " non-zero entries");
        System.out.println(B);

        System.out.println("(1.5)*A= ");
        System.out.println(A.scalarMult(1.5));

        System.out.println("A+B= ");
        System.out.println(A.add(B));

        System.out.println("A+A= ");
        System.out.println(A.add(A));

        System.out.println("B-A+ ");
        System.out.println(B.sub(A));

        System.out.println("A-A= ");
        System.out.println(A.sub(A));

        System.out.println("Transpose(A)");
        System.out.println(A.transpose());

        System.out.println("A*B= ");
        System.out.println(A.mult(B));

        System.out.println("B*B= ");
        System.out.println(B.mult(B));

        in.close();
        out.close();
    }
}
