//package hw1;

public class Interpreter {
    public static void main(String[] args) {
        String Input;
        Parser p = new Parser();

        while (true) {
            Input = p.inputRead();

            if (Input.trim().equalsIgnoreCase("exit")) {
                break;
            }
            
            p.strParser(Input);
        }
    }
}