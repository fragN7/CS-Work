package Exception;

public class ADTEmptyException extends ToyLanguageInterpreterException {
    public ADTEmptyException(String message){
        super(message);
    }
}