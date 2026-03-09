package ce326.hw1;

import java.io.File;

public class Interpreter {
    public static void main(String[] args) {
        
        if (args.length == 0){
            String Input;
            Parser p = new Parser();

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
                    System.out.println("> " + e.getMessage());
                    break;
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
                    System.out.println("> " + e.getMessage());
                    break;
                }
            }
        }
        
    }
}