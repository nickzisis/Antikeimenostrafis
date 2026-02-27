//package hw1;

import java.util.Arrays;
import java.util.Scanner;

public class Parser {
    private Scanner scanner = new Scanner(System.in);
    
    //Reads from the terminal and returns the string read
    public String inputRead() {
        String userInput;
        
        userInput = scanner.nextLine();

        return userInput;
    }

    //Parses the string given to it using the ";" as its thing to split for, then checks if each
    //split ends with the ";"
    public void strParser(String Input) {
        if (!Input.endsWith(";")) {
            System.out.println("Expecting ; at the end of line");
            
            return;
        }

        String Splited[];

        Splited = Input.split(";"); //An thelw na kratisw ; grafw (?=<;)

        System.out.println("Splited string: " + Arrays.toString(Splited));
        //qmarkChecker(Splited);
        Instruction joj = new Instruction();
        for (int i=0 ; i < Splited.length ; i++) {
            String otinane = joj.makis(Splited[i]);
        }
    }

    //Checks for a question mark in every splitted string from the inputed string before
    /*private void qmarkChecker(String[] splittedString) {
        for (int i=0 ; i < splittedString.length ; i++) {
            String test;
            
            test = splittedString[i].trim();
            
            if (!test.endsWith(";")) {
                System.out.println("DEN TELEIWNEI ME ;");
            }
            else {
                System.out.println("TELEIWNEI ME ;");
            }
        }
    }*/
}
