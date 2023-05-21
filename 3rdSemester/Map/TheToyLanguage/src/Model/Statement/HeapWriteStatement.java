package Model.Statement;

import Collection.Dictionary.MyIDictionary;
import Collection.Heap.MyIHeap;
import Model.State.ProgramState;

import Model.Expression.IExpression;
import java.io.IOException;
import Exception.ToyLanguageInterpreterException;
import Model.Type.RefType;
import Model.Type.Type;
import Model.Value.RefValue;
import Model.Value.Value;

public class HeapWriteStatement implements IStatement{

    private final String var;
    private final IExpression exp;

    public HeapWriteStatement(String var, IExpression exp){
        this.var = var;
        this.exp = exp;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException, IOException {

        MyIDictionary<String, Value> symbolTable = state.getSymbolTable();
        MyIHeap<Value> heapTable = state.getHeap();

        if(symbolTable.isDefined(this.var)) {
            Value val = symbolTable.lookup(this.var);
            if(val instanceof RefValue){
                int addr = ((RefValue) val).getAddress();
                if(heapTable.get(addr) != null){
                    Value evalValue = this.exp.evaluate(symbolTable, heapTable);
                    if(evalValue.getType().equals(((RefValue) val).getLocationType())){
                        heapTable.put(addr, evalValue);
                    }
                    else
                        throw new ToyLanguageInterpreterException("Incompatible types.");
                }
                else
                    throw new ToyLanguageInterpreterException("Address is not a key in the heap");
            }
            else
                throw new ToyLanguageInterpreterException("Value not of type Reference type");
        }
        else
            throw new ToyLanguageInterpreterException("Variable not defined");
        return null;
    }

    @Override
    public String toString(){
        return "wH(" + this.var + ", " + this.exp.toString() + ")";
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws ToyLanguageInterpreterException {
        Type typeVar = typeEnv.lookup(this.var);
        Type typeExp = this.exp.typecheck(typeEnv);
        if(typeVar.equals(new RefType(typeExp)))
            return typeEnv;
        else
            throw new ToyLanguageInterpreterException("Heap Write Statement: Different types");
    }
}
