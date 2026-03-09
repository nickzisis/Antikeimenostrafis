//package hw1;

public class Interpreter {
    public static void main(String[] args) {
        String Input;
        Parser p = new Parser();

        while (true) {
            System.out.print("> ");
            Input = p.inputRead();

            if (Input.trim().equalsIgnoreCase("exit")) {
                break;
            }
            try {
                p.strParser(Input);
            } catch (ParserException e){
                System.out.println(e.getMessage());
                break;
            }
        }
    }
}