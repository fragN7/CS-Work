package Collection.Heap;

import java.util.Map;

public interface MyIHeap<T> {

    int allocate(T value);
    T get(int address);
    void put(int address, T value);
    T deallocate(int address);
    Map<Integer, T> getContent();
    void setContent(Map<Integer, T> content);

    String toString();
}
