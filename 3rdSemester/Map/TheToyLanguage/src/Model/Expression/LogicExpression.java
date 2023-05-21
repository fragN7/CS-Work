package Model.Expression;

import Collection.Dictionary.MyIDictionary;
import Collection.Heap.MyIHeap;
import Exception.ToyLanguageInterpreterException;
import Model.Value.*;
import Model.Type.*;

import java.util.Objects;

public class LogicExpression implements IExpression {
    private final IExpression exp1,exp2;
    private final String op;

    public LogicExpression(IExpression exp1, IExpression exp2, String op) {
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.op = op;
    }

    @Override
    public Value evaluate(MyIDictionary<String, Value> table, MyIHeap<Value> heap) throws ToyLanguageInterpreterException {
        Value v1,v2;
        v1 = this.exp1.evaluate(table,heap);
        if (v1.getType().equals(new BooleanType())){
            v2 = this.exp2.evaluate(table,heap);
            if (v2.getType().equals(new BooleanType())){
                BooleanValue i1 = (BooleanValue)v1;
                BooleanValue i2 = (BooleanValue)v2;
                boolean n1,n2;
                n1 = i1.getValue();
                n2 = i2.getValue();
                if (Objects.equals(this.op, "and")){
                    return new BooleanValue(n1 && n2);
                }
                if(Objects.equals(this.op, "or")){
                    return new BooleanValue(n1 || n2);
                }
                else throw new ToyLanguageInterpreterException("Invalid operand");
            }
            else
                throw new ToyLanguageInterpreterException("Second operand is not a bool.");
        }
        else
            throw new ToyLanguageInterpreterException("First second operand is not a bool.");
    }

    @Override
    public String toString() {
        return this.exp1.toString() + " " + this.op + " " + this.exp2.toString();
    }

    @Override
    public Type typecheck(MyIDictionary<String, Type> typeEnv) throws ToyLanguageInterpreterException {
        Type typ1 = this.exp1.typecheck(typeEnv);
        Type typ2 = this.exp2.typecheck(typeEnv);
        if (typ1.equals(new BooleanType()))
            if (typ2.equals(new BooleanType()))
                return new BooleanType();
            else
                throw new ToyLanguageInterpreterException("Second operand is not an integer");
        else
            throw new ToyLanguageInterpreterException("Second operand is not an integer");
    }
}