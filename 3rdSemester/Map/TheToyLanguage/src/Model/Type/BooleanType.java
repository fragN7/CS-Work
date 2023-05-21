package Model.Type;
import Model.Value.BooleanValue;

public class BooleanType implements Type {

    public boolean equals(Object another){
        return another instanceof BooleanType;
    }

    public String toString(){
        return "boolean";
    }

    public BooleanValue defaultValue(){
        return new BooleanValue(false);
    }

}
