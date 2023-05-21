package Model.Statement;

import Collection.Dictionary.MyIDictionary;
import Collection.Stack.MyIStack;
import Model.State.ProgramState;
import Model.Type.Type;
import Exception.ToyLanguageInterpreterException;

public class CompoundStatement implements IStatement {
    private final IStatement first;
    private final IStatement second;

    public CompoundStatement(IStatement first, IStatement second){
        this.first = first;
        this.second = second;
    }

    @Override
    public ProgramState execute(ProgramState state) {
        MyIStack<IStatement> stack = state.getExecutionStack();
        stack.push(this.second);
        stack.push(this.first);
        state.setExecutionStack(stack);
        return null;
    }

    @Override
    public String toString(){
        return this.first.toString() + "; " + this.second.toString();
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws ToyLanguageInterpreterException {
          return this.second.typecheck(this.first.typecheck(typeEnv));
    }
}
