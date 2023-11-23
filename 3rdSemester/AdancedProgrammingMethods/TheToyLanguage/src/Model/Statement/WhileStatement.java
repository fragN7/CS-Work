package Model.Statement;

import Exception.ToyLanguageInterpreterException;
import Model.Expression.IExpression;
import Model.State.ProgramState;
import Model.Type.BooleanType;
import Model.Type.Type;
import Model.Value.BooleanValue;
import Model.Value.Value;
import Collection.Dictionary.*;
import java.io.IOException;

public class WhileStatement implements IStatement{

    private final IExpression exp;
    private final IStatement statement;

    public WhileStatement(IExpression exp, IStatement statement){
        this.exp = exp;
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException, IOException {
        MyIDictionary<String, Value> symbolTable = state.getSymbolTable();
        Value result = exp.evaluate(symbolTable,state.getHeap());
        if (result.getType().equals(new BooleanType())){
            BooleanValue downcastedResult = (BooleanValue)result;
            if (downcastedResult.getValue()){
                state.getExecutionStack().push(new WhileStatement(exp,statement));
                state.getExecutionStack().push(statement);
            }
        }
        else
            throw new ToyLanguageInterpreterException("Condition exp is not a boolean.");
        return null;
    }

    @Override
    public String toString() {
        return "(while(" + this.exp.toString() + ")" + this.statement.toString()+")";
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws ToyLanguageInterpreterException {
        Type type = this.exp.typecheck(typeEnv);
        if(type.equals(new BooleanType()))
            return typeEnv;
        else
            throw new ToyLanguageInterpreterException("The condition of WHILE has not the type boolean");
    }
}
