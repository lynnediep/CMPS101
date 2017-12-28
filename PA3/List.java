//Lynne Diep                                                                                                                                                                         
//lytdiep@ucsc.edu                                                                                                                                                                   
//CMPS 101                                                                                                                                                                           
//PA 3                                                                                                                                                                               
//List.java                                                                                                                                                                          


//FIXED toString() - was tmp.entry instead of tmp.data!                                                                                                                              
public class List {

    private class Node {
        Object data;
        Node previous;
        Node next;

        Node(Object data) {
            this.data = data;
            previous = null;
            next = null;
        }

        Node(Object data, Node previous, Node next){
            this.data = data;
            this.previous = previous;
            this.next = next;
        }

        public String toString(){
            return String.valueOf(data);
        }


        public boolean equals(Object x){
            boolean eq = false;
            Node that;
            if(x instanceof Node){
                that = (Node) x;
		eq = (this.data==that.data);
            }
            return eq;
        }
    }


    private Node front;
    private Node back;
    private Node cursor;
    private int length;
    private int index;

    public List(){               //Creates new empty list                                                                                                                            
        index = -1;
        length = 0;
	front = null;
        back = null;
        cursor = null;
    }

    //ACCESS FUNCTIONS                                                                                                                                                               
    int length(){
        return length;
    }

    int index(){
        return index;
    }

    Object front(){
        if(length <= 0){
            throw new RuntimeException("List Error:front() called on empty list");
        }
        return front.data;
    }

    Object back(){
        if(length <= 0){
            throw new RuntimeException("List Error:back() called on empty list");
        }
        return back.data;
    }

    Object get(){
	  if(length <= 0){
            throw new RuntimeException("List Error: get() called on empty list");
        }
        if(index < 0){
            throw new RuntimeException("List Error: get() called on an unassigned index");
        }
        return cursor.data;
    }

    boolean equals(List L){    // Returns true if this List and L are the same integer                                                                                               
        boolean flag = true;   // USED Queue.java AS TEMPLATE                                                                                                                        
        Node n;
        Node m;

        if(L.length == length){
            n = front;
            m = L.front;
            while(flag && n!=null){
                flag = (n.data==m.data);
                n = n.next;
                m = m.next;
            }
            return flag;
        }
        else{
            return false;

   	 }

    void clear() {               //resets list to its original empty state                                                                                                           
        front = null;
        back = null;
        cursor = null;
        length = 0;
        index = -1;
    }

    void moveFront(){
        if (length>0){
            cursor = front;
            index = 0;
        }
    }

    void moveBack(){
        if(length>0){
            cursor = back;
            index = length - 1;
        }
    }

	    
    void movePrev(){
        if(cursor != null && index != 0){
		cursor = cursor.previous;
            	index = (index-1);
        }
        else if(cursor != null && index==0){
            cursor = null;
            index = -1;
        }
    }

    void moveNext(){
        if(cursor != null && index != (length-1)){
            cursor = cursor.next;
            index = (index+1);
        }
        else if(cursor != null && index==(length-1)){
            cursor = null;
            index = -1;
        }
    }

    void prepend(Object data){
        Node newEle = new Node(data);
        if( length <= 0){
            front = back = newEle;
            length++;
        }
        else{
            front.previous = newEle;
	    newEle.next = front;
            front = newEle;
            index++;
            length++;
        }

    }

    void append(Object data){
        Node newEle = new Node(data);
        if( length <= 0){
            back = front = newEle;
        }
        else{
            back.next = newEle;
            newEle.previous = back;
            back = newEle;
        }
        length++;

    }

    void insertBefore(Object data){
        if(length <= 0){
            throw new RuntimeException("List Error: insertBefore called on empty list");
        }
        if(index < 0){
	    throw new RuntimeException("List Error: insertBefore called on undefined index");
        }
        Node temp = new Node(data,cursor.previous, cursor);
        if(cursor.previous != null){
            cursor.previous.next = temp;
        }
        else{
            cursor.previous = null;
            front = temp;
            cursor.previous = temp;
            ++length;
        }
    }

    void insertAfter(Object data){
        if(index < 0){
            throw new RuntimeException("List Error: insertAfter() called on undefined index");
        }
        if(length <= 0){
            throw new RuntimeException("List Error: insertAfter() called on an empty List");
        }
        Node temp = new Node(data, cursor, cursor.next);
        if(cursor.next != null)
            cursor.next.previous = temp;
        else{
            cursor.next = null;
            back = temp;
	    cursor.next = temp;
            ++length;
        }
    }

    void deleteFront(){
        if(length <= 0){
            throw new RuntimeException("List Error: deleteFront called on empty list");
        }
        else {
            front = front.next;
            front.previous = null;
            --length;
        }
    }

    void deleteBack(){
        if(length <= 0){
            throw new RuntimeException("List Error: deleteBack called on empty list");
        }
        else{
            back = back.previous;
            back.next = null;
            --length;
        }
    }

 void delete(){
        if (length <= 0){
            throw new RuntimeException("List Error: delete called on empty list");
        }
        if(length < 0){
            throw new RuntimeException("List Error: delete called on undefined indext");
        }
        else{
            cursor.previous.next = cursor.next;
            cursor.next.previous = cursor.previous;
            cursor = null;
            index = -1;
            --length;
        }
    }

    public String toString(){
        Node tmp = front;
        String output = new String();
        String space = "";
        while(tmp != null) {
            output += space + tmp.data;
            tmp = tmp.next;
            space = " ";
        }
        return output;
    }
}
