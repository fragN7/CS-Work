package Model.Statement;

import Collection.Dictionary.MyIDictionary;
import Collection.Heap.MyIHeap;
import Model.Expression.IExpression;
import Model.State.ProgramState;
import Exception.ToyLanguageInterpreterException;
import Model.Type.RefType;
import Model.Type.Type;
import Model.Value.RefValue;
import Model.Value.Value;

import java.io.IOException;

public class NewStatement implements IStatement{

    private final String varName;
    private final IExpression exp;

    public NewStatement(String varName, IExpression exp){
        this.varName = varName;
        this.exp = exp;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException, IOException {

        MyIDictionary<String, Value> symbolTable = state.getSymbolTable();
        MyIHeap<Value> heapTable = state.getHeap();

        if(symbolTable.isDefined(varName)){
            Value val = symbolTable.lookup(varName);
            if(val instanceof RefValue){
                Value expValue = this.exp.evaluate(symbolTable, heapTable);
                if(expValue.getType().equals(((RefValue) val).getLocationType())){
                    int location = heapTable.allocate(expValue);
                    symbolTable.update(varName, new RefValue(location, expValue.getType()));
                }
                else
                    throw new ToyLanguageInterpreterException("Types are not equal");
            }
            else
                throw new ToyLanguageInterpreterException("Value isn't of type Reference");
        }
        else
            throw new ToyLanguageInterpreterException("Variable not defined");
        return null;
    }

    @Override
    public String toString(){
        return "new(" + this.exp.toString() + ")";
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws ToyLanguageInterpreterException {
        Type typeVar = typeEnv.lookup(this.varName);
        Type typeExp = this.exp.typecheck(typeEnv);
        if(typeVar.equals(new RefType(typeExp)))
            return typeEnv;
        else
            throw new ToyLanguageInterpreterException("New Statement: right hand side and left hand side have different types");
    }
}
