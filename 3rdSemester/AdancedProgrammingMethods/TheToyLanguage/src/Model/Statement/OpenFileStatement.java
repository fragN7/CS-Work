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

public class OpenFileStatement implements IStatement{

    private final IExpression expression;

    public OpenFileStatement(IExpression expression){
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException, FileNotFoundException {

        MyIDictionary<String, Value> symbolTable = state.getSymbolTable();
        MyIHeap<Value> heapTable = state.getHeap();

        Value evalValue = this.expression.evaluate(symbolTable, heapTable);
        if(evalValue.getType().equals(new StringType())) {
            StringValue downValue = (StringValue) evalValue;
            String expressionValue = downValue.getValue();
            if (!state.getFileTable().isDefined(expressionValue)) {
                BufferedReader fileDesc = new BufferedReader(new FileReader(expressionValue));
                state.getFileTable().update(expressionValue, fileDesc);
            } else
                throw new ToyLanguageInterpreterException("Filename already exists!");
        }
        else
            throw new ToyLanguageInterpreterException("Expression doesn't evaluate to a string!");
        return null;
    }

    @Override
    public String toString() {
        return "open(" + this.expression.toString() + ")";
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws ToyLanguageInterpreterException {
        Type typeExp = this.expression.typecheck(typeEnv);
        if(typeExp.equals(new StringType()))
            return typeEnv;
        else
            throw new ToyLanguageInterpreterException("Read Statement: expression is not a string");
    }
}
