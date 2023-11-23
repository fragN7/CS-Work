package Model.Value;

import Model.Type.Type;
import Model.Type.StringType;

public class StringValue implements Value{

    private final String value;

    public StringValue(String value) {
        this.value = value;
    }

    public String getValue() {
        return this.value;
    }

    @Override
    public boolean equals(Object another) {
        return another instanceof StringType;
    }

    @Override
    public String toString() {
        return String.valueOf(this.value);
    }

    @Override
    public Type getType() {
        return new StringType();
    }
}
