package Model.Value;

import Model.Type.RefType;
import Model.Type.Type;

public class RefValue implements Value{

    private final int address;
    private final Type locationType;

    public RefValue(int address, Type locationType) {
        this.address = address;
        this.locationType = locationType;
    }

    public Type getLocationType() {
        return this.locationType;
    }

    public int getAddress() {
        return this.address;
    }

    public String toString() {
        return "("+ this.address + "," + this.locationType.toString() +  ")";
    }

    @Override
    public Type getType() {
        return new RefType(this.locationType);
    }


}
