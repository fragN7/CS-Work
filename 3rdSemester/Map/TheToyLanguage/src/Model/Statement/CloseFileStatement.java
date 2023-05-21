package Model.Statement;

import Collection.Dictionary.MyIDictionary;
import Collection.Heap.MyIHeap;
import Exception.ToyLanguageInterpreterException;
import Model.State.ProgramState;
import Model.Type.StringType;
import Model.Type.Type;
import Model.Value.StringValue;
import Model.Value.Value;

import Model.Expression.IExpression;
import java.io.*;

public class CloseFileStatement implements IStatement{

    private final IExpression expression;

    public CloseFileStatement(IExpression expression){
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException, IOException {

        MyIDictionary<String, Value> symbolTable = state.getSymbolTable();
        MyIHeap<Value> heapTable = state.getHeap();

        Value evalValue;
        evalValue = this.expression.evaluate(symbolTable, heapTable);
        if(evalValue.getType().equals(new StringType())){
            StringValue downValue = (StringValue) evalValue;
            String expValue = downValue.getValue();
            if(state.getFileTable().isDefined(expValue)){
                BufferedReader fileDesc = state.getFileTable().get(expValue);
                fileDesc.close();
                state.getFileTable().delete(expValue);
            }
            else
                throw new ToyLanguageInterpreterException("File name doesn't exist!");
        }
        else
            throw new ToyLanguageInterpreterException("Expression is not a string");
        return null;
    }

    @Override
    public String toString(){
        return "close(" + this.expression.toString() + ")";
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws ToyLanguageInterpreterException {
        Type typeExp = this.expression.typecheck(typeEnv);
        if(typeExp.equals(new StringType()))
            return typeEnv;
        else
            throw new ToyLanguageInterpreterException("Close File Statement: expression is not a string");
    }
}
