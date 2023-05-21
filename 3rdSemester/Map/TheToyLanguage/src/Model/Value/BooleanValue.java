package Model.Value;

import Model.Type.BooleanType;
import Model.Type.Type;

public class BooleanValue implements Value{

    private final boolean value;

    public BooleanValue(boolean value){
        this.value = value;
    }

    public Boolean getValue(){
        return value;
    }
    @Override
    public boolean equals(Object another){
        return another instanceof BooleanType;
    }

    @Override
    public String toString(){
        return String.valueOf(this.value);
    }
    public Type getType(){
        return new BooleanType();
    }

}
