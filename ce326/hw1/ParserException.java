


public class ParserException extends Exception {

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