package Model.Expression;

import Collection.Dictionary.MyIDictionary;
import Collection.Heap.MyIHeap;
import Exception.ToyLanguageInterpreterException;
import Model.Type.Type;
import Model.Value.Value;

public interface IExpression {
    Value evaluate(MyIDictionary<String, Value> symbolTable, MyIHeap<Value> heapTable) throws ToyLanguageInterpreterException;
    Type typecheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException;
    String toString();
}
