package Model.Value;

import Model.Type.IntType;
import Model.Type.Type;

public class IntValue implements Value {
    private final int value;

    public IntValue(int v) {
        this.value = v;
    }

    public int getValue() {
        return value;
    }

    @Override
    public boolean equals(Object another){
        return another instanceof IntType;
    }

    @Override
    public String toString(){
        return String.valueOf(this.value);
    }

    public Type getType(){
        return new IntType();
    }
}
