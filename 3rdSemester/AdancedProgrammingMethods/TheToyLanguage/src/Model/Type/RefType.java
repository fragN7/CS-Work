package Model.Type;

import Model.Value.RefValue;
import Model.Value.Value;

public class RefType implements Type{

    private final Type inner;

    public RefType(Type inner){
        this.inner = inner;
    }

    public Type getInner(){
        return this.inner;
    }

    public boolean equals(Object another){
        if(another instanceof RefType)
            return inner.equals(((RefType) another).getInner());
        else
            return false;
    }

    public String toString(){
        return "Ref{" + this.inner.toString() + "}";
    }
    @Override
    public Value defaultValue() {
        return new RefValue(0, this.inner);
    }
}
