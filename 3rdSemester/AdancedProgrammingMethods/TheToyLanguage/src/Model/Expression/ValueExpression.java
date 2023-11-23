package Model.Expression;

import Collection.Dictionary.MyIDictionary;
import Collection.Heap.MyIHeap;
import Model.Type.Type;
import Model.Value.Value;
import Exception.ToyLanguageInterpreterException;


public class ValueExpression implements IExpression{
    Value value;

    public ValueExpression(Value value) {
        this.value = value;
    }

    @Override
    public Value evaluate(MyIDictionary<String, Value> symbolTable, MyIHeap<Value> heapTable){
        return this.value;
    }

    @Override
    public String toString(){return this.value.toString();}

    @Override
    public Type typecheck(MyIDictionary<String, Type> typeEnv) {
        return this.value.getType();
    }
}
