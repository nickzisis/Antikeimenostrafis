//package hw1;

import java.util.Deque;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Scanner;


public class Parser {
    private Scanner scanner = new Scanner(System.in);
    private HashMap<String, Double> variables = new HashMap<>();
    
    //Reads from the terminal and returns the string read
    public String inputRead() {
        String userInput;

        userInput = scanner.nextLine();

        return userInput;
    }

    //Parses the string given to it using the ";" as its thing to split for, then checks if each
    //split ends with the ";"
    public void strParser(String Input) throws ParserException{
        if (!Input.trim().endsWith(";")) {
            System.out.println("Expecting ; at the end of line");
            
            return;
        }

        String Splited[];
        String variableName = "";
        boolean hasAssigned = false, hasPrint = false;

        Splited = Input.split(";");
    
        for (String Splited1 : Splited) {
            try {
                Instruction instr = new Instruction(Splited1);
                LinkedList<String> tokenList = instr.tokenMaker();
                
                //Checks if we want to add a new variable, if yes then the hasAssigned becomes true.
                if ((tokenList.size() >= 2) && (tokenList.get(1).equals("="))) {
                    variableName = tokenList.get(0);
                    hasAssigned = true;
                    
                    tokenList.remove(0);
                    tokenList.remove(0); 
                }
                //Checks if we have to print, if yes then the hasPrint becomes true.
                else if ((!tokenList.isEmpty()) && (tokenList.get(0).equals("print"))) {
                    hasPrint = true;
                    
                    tokenList.remove(0);
                }
                
                instr.errorChecker(tokenList);
                Deque<String> SYResult = instr.ShuntingYard(tokenList);
                double result = instr.RPNcalculator(SYResult, this.variables);

                if (hasAssigned) {
                    //Assigns the new variable to the hashmap.
                    this.variables.put(variableName, result);
                }
                else if(hasPrint) {
                    //Prints.
                    if (result == Math.floor(result)) {
                        System.out.println("  " + (int)result);
                    } else {
                        System.out.printf("  %.6f\n", result);
                    }
                }
            }catch (ParserException e){
                System.out.println(e.getMessage());
                break;
            }
        }
    }

}
