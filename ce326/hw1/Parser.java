package ce326.hw1;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Deque;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Scanner;


public class Parser {
    private Scanner scanner;
    private HashMap<String, Double> variables = new HashMap<>();
    
    //Constructors for the parser, one for standard input and one for file input.
    public Parser(){
        this.scanner = new Scanner(System.in);
    }
    public Parser(File inputFile){
        try{
            this.scanner = new Scanner(inputFile);
        } catch (FileNotFoundException e){
        }
    }

    // Reads the input from the user, if there is no input then it returns null.
    public String inputRead() {
        String userInput;
        
        if (scanner.hasNextLine()){
            userInput = scanner.nextLine();
        } else {
            userInput = null;
        }
            
            return userInput;
    }

    //Parses the string given to it using the ";" as its thing to split for, then checks if each
    //split ends with the ";"
    public void strParser(String Input) throws ParserException{
        if (!Input.trim().endsWith(";")) {
            throw new ParserException("Expecting ; at the end of line");
        }

        String Splited[];
        String variableName = "";
        boolean hasAssigned = false, hasPrint = false;

        Splited = Input.split(";");
    
        for (String Splited1 : Splited) {
            try {
                Instruction instr = new Instruction(Splited1);
                LinkedList<String> tokenList = instr.tokenMaker();
                instr.errorChecker(tokenList);

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
                
                Deque<String> SYResult = instr.ShuntingYard(tokenList);
                double result = instr.RPNcalculator(SYResult, this.variables);

                if (hasAssigned) {
                    //Assigns the new variable to the hashmap.
                    this.variables.put(variableName, result);
                }
                else if(hasPrint) {
                    //Prints.
                    if (result - Math.floor(result) > 0.000001) {
                        System.out.printf("  %.6f\n", result);
                    } else {
                        System.out.println("  " + (int)result);
                    }
                }
            }catch (ParserException e){
                System.out.println(e.getMessage());
                break;
            }
        }
    }
}
