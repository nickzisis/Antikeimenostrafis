package ce326.hw1;

import java.io.File;

public class Interpreter {
    public static void main(String[] args) {
        // If there are no arguments, read from standard input. 
        // Otherwise, read from the file specified in the first argument.
        if (args.length == 0){
            String Input;
            Parser p = new Parser();

            while (true) {
                System.out.print("> ");
                Input = p.inputRead();
                
                if (Input == null){
                    break;
                }

                if (Input.length() < 1) {
                    continue;
                }
                
                if (Input.trim().equalsIgnoreCase("exit")) {
                    break;
                }
                try{
                    p.strParser(Input);
                } catch (ParserException e){
                    System.out.println(e.getMessage());
                }
            }
        } else {
            String Input;
            Parser p = new Parser(new File(args[0]));

            while (true) {
                System.out.print("> ");
                Input = p.inputRead();
                
                if (Input == null){
                    break;
                }

                if (Input.trim().equalsIgnoreCase("exit")) {
                    break;
                }
                try{
                    p.strParser(Input);
                } catch (ParserException e){
                    System.out.println(e.getMessage());
                    break;
                }
            }
        }
    }
}