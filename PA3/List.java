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
