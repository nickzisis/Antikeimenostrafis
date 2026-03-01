//package hw1;

import java.util.Arrays;
import java.util.LinkedList;
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
    public void strParser(String Input) throws ParserException{
        if (!Input.endsWith(";")) {
            System.out.println("Expecting ; at the end of line");
            
            return;
        }

        String Splited[];

        Splited = Input.split(";"); //An thelw na kratisw ; grafw (?=<;)

        System.out.println("Splited string: " + Arrays.toString(Splited));
    
        
        for (String Splited1 : Splited) {
            try {
                Instruction instr = new Instruction(Splited1);
                LinkedList<String> tokenList = instr.tokenMaker();
                instr.errorChecker(tokenList);
                
                // instr.RPNcalculator();
            }catch (ParserException e){
                System.out.println(e.getMessage());
                break;
            }
        }
    }

}
