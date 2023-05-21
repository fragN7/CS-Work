package Exception;

public class VariableNotFoundException extends ToyLanguageInterpreterException{
    public VariableNotFoundException(String message){
        super(message);
    }
}
