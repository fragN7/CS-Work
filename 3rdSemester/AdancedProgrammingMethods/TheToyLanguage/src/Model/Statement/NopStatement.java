package Model.Statement;

import Collection.Dictionary.MyIDictionary;
import Model.State.ProgramState;
import Model.Type.RefType;
import Model.Type.Type;
import Exception.ToyLanguageInterpreterException;


public class NopStatement implements IStatement {

    @Override
    public ProgramState execute(ProgramState state) {
        return null;
    }

    @Override
    public String toString() {
        return "No Operation Statement";
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws ToyLanguageInterpreterException {
        return typeEnv;
    }
}
