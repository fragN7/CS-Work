package Model.Type;
import Model.Value.IntValue;

public class IntType implements Type{

    public boolean equals(Object another){
        return another instanceof IntType;
    }

    public String toString(){
        return "int";
    }

    public IntValue defaultValue(){
        return new IntValue(0);
    }
}
