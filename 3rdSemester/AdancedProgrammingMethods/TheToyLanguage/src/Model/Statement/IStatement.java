package Model.Statement;

import Collection.Dictionary.MyIDictionary;
import Exception.ToyLanguageInterpreterException;
import Model.State.ProgramState;
import Model.Type.Type;
import java.io.IOException;

public interface IStatement {
    ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException, IOException;
    String toString();
    MyIDictionary<String,Type> typecheck(MyIDictionary<String, Type> typeEnv) throws ToyLanguageInterpreterException;
}

