package Model.Statement;

import Collection.Dictionary.MyIDictionary;
import Collection.Stack.MyIStack;
import Collection.Stack.MyStack;
import Model.State.ProgramState;
import Exception.ToyLanguageInterpreterException;
import Model.Type.Type;

import java.io.IOException;

public class ForkStatement implements IStatement{

    private IStatement statement;

    public ForkStatement(IStatement statement){
        this.statement = statement;
    }

    public IStatement getStatement() {
        return statement;
    }

    public void setStatement(IStatement statement) {
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException, IOException {
        MyIStack<IStatement> statementStack = new MyStack<>();
        statementStack.push(this.statement);
        return new ProgramState(statementStack, state.getSymbolTable().clone_dict(), state.getOutputList(),
                this.statement, state.getHeap(), state.getFileTable());
    }

    @Override
    public String toString() {
        return "fork(" + this.statement.toString() + ")";
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws ToyLanguageInterpreterException {
        this.statement.typecheck(typeEnv.clone_dict());
        return typeEnv;
    }
}
