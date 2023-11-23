package Model.Expression;

import Collection.Heap.MyIHeap;
import Exception.ToyLanguageInterpreterException;
import Collection.Dictionary.MyIDictionary;
import Model.Type.BooleanType;
import Model.Type.IntType;
import Model.Type.Type;
import Model.Value.BooleanValue;
import Model.Value.IntValue;
import Model.Value.Value;

public class RelationalExpression implements IExpression {

    private final IExpression exp1, exp2;
    private final String op;

    public RelationalExpression(IExpression exp1, IExpression exp2, String op){
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.op = op;
    }

    @Override
    public Value evaluate(MyIDictionary<String, Value> symbolTable, MyIHeap<Value> heapTable) throws ToyLanguageInterpreterException {

        Value value1, value2;
        value1 = this.exp1.evaluate(symbolTable, heapTable);
        if(value1.getType().equals(new IntType())){
            value2 = this.exp2.evaluate(symbolTable, heapTable);
            if(value2.getType().equals(new IntType())){
                IntValue int1 = (IntValue) value1;
                IntValue int2 = (IntValue) value2;
                int num1, num2;
                num1 = int1.getValue();
                num2 = int2.getValue();
                return switch (op) {
                    case ">" -> new BooleanValue(num1 > num2);
                    case "<" -> new BooleanValue(num1 < num2);
                    case "<=" -> new BooleanValue(num1 <= num2);
                    case ">=" -> new BooleanValue(num1 >= num2);
                    case "==" -> new BooleanValue(num1 == num2);
                    case "!=" -> new BooleanValue(num1 != num2);
                    default -> throw new ToyLanguageInterpreterException("Invalid operator");
                };
            }
            else
                throw new ToyLanguageInterpreterException("Second operand is not an int!");
        }
        else
            throw new ToyLanguageInterpreterException("First operand is not an int");
    }

    @Override
    public String toString(){
        return this.exp1.toString() + this.op + this.exp2.toString();
    }

    @Override
    public Type typecheck(MyIDictionary<String,Type> typeEnv) throws ToyLanguageInterpreterException{
        Type typ1 = this.exp1.typecheck(typeEnv);
        Type typ2 = this.exp2.typecheck(typeEnv);
        if (typ1.equals(new IntType()))
            if (typ2.equals(new IntType()))
                return new BooleanType();
            else
                throw new ToyLanguageInterpreterException("Second operand is not an integer");
        else
            throw new ToyLanguageInterpreterException("First operand is not an integer");
    }

}
