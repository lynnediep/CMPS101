// Lynne Diep                                                                                                                                                                        
// lytdiep@ucsc.edu                                                                                                                                                                  
// CMPS 101                                                                                                                                                                          
// PA1                                                                                                                                                                               
// Lex.java                                                                                                                                                                          

import java.io.*;
import java.util.Scanner;

public class Lex{
    public static void main(String[] args) throws IOException{
        Scanner in = null;
        PrintWriter out = null;
        String line = null;
        String[] token = null;
        int lineNumber = 0;

        if(args.length < 2){                                                    //check that there are 2 command line arguments                                                      
            System.out.println("Usage: There are not 2 command line arguments");
            System.exit(1);
        }

        if(args.length > 2){
            System.out.println("Usage: FileIO infile outfile");
            System.exit(1);
        }

        in = new Scanner(new File(args[0]));                                   //get file                                                                                            

        while(in.hasNextLine() ) {                                             //count # of lines                                                                                    
            lineNumber++;
            in.nextLine();
        }

        in.close();                                                            //close file                                                                                          

        List list = new List();                                                //create new list                                                                                     
        token = new String[lineNumber];                                        //create array of length lineNumber                                                                   
        in = new Scanner(new File(args[0]));                                   //get file                                                                                            
        out = new PrintWriter(new FileWriter(args[1]));

        for(int i = 0; i < lineNumber; i++) {                                  //read in the lines of file, place in array                                                           
            line = in.nextLine()+" ";                                          //add extra space so split works right                                                                
            token[i] = line;
        }

        list.append(0);

        for(int j = 1; j < token.length; j++){                                 //insertion sort                                                                                      
            String key = token[j];
            int i = j-1;
            list.moveBack();

         while(key.compareTo(token[list.back()]) <=  0 && i >= 0){           //compare each line of list                                                                          
                i--;
                list.movePrev();
            }
            if(list.index() >= 0){
                list.insertAfter(j);
            }
            if(list.index() < 0){                                              //fell off list                                                                                       
                list.prepend(j);
            }
        }

        list.moveFront();

        while(list.index() >= 0){                                             //print out sorted list                                                                                
            out.println(token[list.get()]);
            list.moveNext();
        }

        in.close();                                                           //close in file                                                                                        
        out.close();                                                          //close out file                                                                                       

    }//closes IOException                                                                                                                                                            

}// closes public class Lex                          
