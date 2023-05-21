package Collection.List;

import java.util.ArrayList;

public class MyList<T> implements MyIList<T> {
    private final ArrayList<T> list;

    public MyList(){
        this.list = new ArrayList<T>();
    }

    @Override
    public int size(){
        return this.list.size();
    }

    @Override
    public boolean isEmpty() {
        return this.list.isEmpty();
    }

    @Override
    public boolean add(T e){
        return this.list.add(e);
    }

    @Override
    public void clear(){
        this.list.clear();
    }

    @Override
    public T get(int index){
        return this.list.get(index);
    }

    @Override
    public String toString(){
        return this.list.toString();
    }
}
