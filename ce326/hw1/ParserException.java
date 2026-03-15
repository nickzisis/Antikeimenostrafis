package ce326.hw1;

//This class is used to create a custom exception for the parser, 
// it extends the Exception class and has a message field to store the error message.
public class ParserException extends Exception {
    private static final long serialVersionUID = 1L;
    String message;

    public ParserException(String message){
        super(message);
        this.message = message;
    }

    @Override
    public String getMessage() {
        return this.message;
    }
}   