package Model.Statement;

import Collection.Dictionary.MyIDictionary;
import Collection.Heap.MyIHeap;
import Exception.ToyLanguageInterpreterException;
import Model.State.ProgramState;
import Model.Type.IntType;
import Model.Type.RefType;
import Model.Type.StringType;
import Model.Type.Type;
import Model.Value.IntValue;
import Model.Value.StringValue;
import Model.Value.Value;

import Model.Expression.IExpression;
import java.io.*;

public class ReadFileStatement implements IStatement{

    private final IExpression expression;
    private final String var;

    public ReadFileStatement(IExpression expression, String var){
        this.expression = expression;
        this.var = var;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException, IOException {

        MyIDictionary<String, Value> symbolTable = state.getSymbolTable();
        MyIHeap<Value> heapTable = state.getHeap();

        if(state.getSymbolTable().isDefined(var)) {
            if(state.getSymbolTable().lookup(var).getType().equals(new IntType())){
                Value evalValue;
                evalValue = this.expression.evaluate(symbolTable, heapTable);
                if(evalValue.getType().equals(new StringType())){
                    StringValue downValue = (StringValue) evalValue;
                    String expValue = downValue.getValue();
                    if(state.getFileTable().isDefined(expValue)){
                        BufferedReader fileDesc = state.getFileTable().lookup(expValue);
                        String line = fileDesc.readLine();
                        IntValue readValue;
                        if(line == null)
                            readValue = new IntValue(0);
                        else
                            readValue = new IntValue(Integer.parseInt(line));
                        state.getSymbolTable().update(this.var, readValue);
                    }
                    else
                        throw new ToyLanguageInterpreterException("No entry in file table!");
                }
                else
                    throw new ToyLanguageInterpreterException("Expression not a string");
            }
            else
                throw new ToyLanguageInterpreterException("Value type is not int");
        }
        else
            throw new ToyLanguageInterpreterException("Variable name not defined in symbol table");
        return null;
    }

    @Override
    public String toString() {
        return "read(" + this.expression.toString() + ";" + this.var + ")";
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws ToyLanguageInterpreterException {
        Type typeVar = typeEnv.lookup(this.var);
        Type typeExp = this.expression.typecheck(typeEnv);
        if(typeVar.equals(new RefType(typeExp)))
            if(typeVar.equals(new RefType(typeExp))) {
                return typeEnv;
            }
            else
                throw new ToyLanguageInterpreterException("Read File Statement: expression is not a string");
        else
            throw new ToyLanguageInterpreterException("Read File Statement: variable is not of type int");
    }
}
