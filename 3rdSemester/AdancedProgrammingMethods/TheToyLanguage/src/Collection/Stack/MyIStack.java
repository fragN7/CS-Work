package Collection.Stack;

import Exception.ADTEmptyException;

import java.util.List;

public interface MyIStack<T> {
    T pop() throws ADTEmptyException;
    void push(T v);
    boolean isEmpty();
    String toString();

    List<T> getAll();

    int size();

}
