//Lynne Diep                                                                                                                                                                         
//lytdiep@ucsc.edu                                                                                                                                                                   
//CMPS 101                                                                                                                                                                           
//PA 1                                                                                                                                                                               
//List.java                                                                                                                                                                          

public class List {

    private class Node {
        int data;
        Node previous;
        Node next;

        Node(int data) {
            this.data = data;
            previous = null;
            next = null;
        }

        Node(int data, Node previous, Node next){
          this.data = data;
          this.previous = previous;
          this.next = next;
          }

        public String toString(){
            return String.valueOf(data);
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
    int length(){                // Returns the number of elements in this List.                                                                                                     
        return length;
    }

    int index(){                 // If cursor is defined, returns the index of the cursor element,                                                                                   
        return index;            // otherwise, returns -1                                                                                                                            
    }
    
  int front(){                 // Returns front element. Pre: length()>0                                                                                                           
        if(length <= 0){
            throw new RuntimeException("List Error:front() called on empty list");
        }
        return front.data;
    }

    int back(){                 // Returns back element. Pre: length()>0                                                                                                             
        if(length <= 0){
            throw new RuntimeException("List Error: back() called on empty list");
        }
        return back.data;
    }

    int get(){                  // Returns cursor element. Pre: length()>0, index()>=0                                                                                               
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

    }

    //MANIPULATION PROCEDURES                                                                                                                                                        

    void clear() {                         //resets list to its original empty state                                                                                                 
        front = null;
        back = null;
        cursor = null;
        length = 0;
        index = -1;
}

    void moveFront(){                     //if list is non empty, cursor in front of element                                                                                         
        if(length > 0){
            cursor = front;
            index = 0;
        }
    }

    void moveBack(){                      //if list is non empty, cursor back of elemtn                                                                                              
        if(length > 0){
            cursor = back;
            index = length-1;             //back element                                                                                                                             
        }
    }

    void movePrev(){                      //if cursor is defined/not in front - move one step toward list                                                                            
        if(cursor != null && index != 0){
            cursor = cursor.previous;
            index = (index-1);
        }
        else if(cursor != null && index==0){// if cursor is defined/front - cursor = null                                                                                            
            cursor = null;
            index = -1;
        }
    }
