package Collection.Heap;

import java.util.HashMap;
import java.util.Map;

public class MyHeap<T> implements MyIHeap<T>{


    private HashMap<Integer, T> map;
    private int memory;

    public MyHeap() {
        this.map = new HashMap<Integer, T>();
        this.memory = 0;
    }

    @Override
    public synchronized int allocate(Object value) {
        this.memory++;
        this.map.put(this.memory, (T) value);
        return this.memory;
    }

    @Override
    public T get(int address) {
        return this.map.get(address);
    }

    @Override
    public void put(int address, T value) {
        this.map.put(address, (T) value);
    }

    @Override
    public synchronized T deallocate(int address) {
        return this.map.remove(address);
    }

    @Override
    public Map<Integer, T> getContent() {
        return this.map;
    }

    @Override
    public void setContent(Map<Integer, T> content) {
        this.map = (HashMap) content;
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder("{");
        for(HashMap.Entry<Integer,T> entry : this.map.entrySet()){
            s.append(entry.getKey().toString()).append("->").append(entry.getValue().toString()).append("\n");
        }
        s.append("}");
        return s.toString();
    }
}
