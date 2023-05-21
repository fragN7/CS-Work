package Model.Expression;

import Collection.Dictionary.MyIDictionary;
import Collection.Heap.MyIHeap;
import Exception.ToyLanguageInterpreterException;
import Model.Type.Type;
import Model.Value.Value;

public class VariableExpression implements  IExpression{
    String key;

    public VariableExpression(String key){
        this.key = key;
    }

    @Override
    public Value evaluate(MyIDictionary<String, Value> symbolTable, MyIHeap<Value> heapTable) throws ToyLanguageInterpreterException {
        return symbolTable.get(key);
    }

    @Override
    public String toString(){
        return key;
    }

    @Override
    public Type typecheck(MyIDictionary<String, Type> typeEnv) throws ToyLanguageInterpreterException {
        return typeEnv.lookup(key);
    }
}
