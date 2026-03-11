package ce326.hw1;


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