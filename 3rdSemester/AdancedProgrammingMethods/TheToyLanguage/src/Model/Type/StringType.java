package Model.Type;

import Model.Value.StringValue;
import Model.Value.Value;

public class StringType implements Type{

    public boolean equals(Object another) {
        return another instanceof StringType;
    }

    @Override
    public String toString() {
        return "string";
    }

    @Override
    public Value defaultValue(){
        return new StringValue("");
    }
}
