package Collection.Stack;

import Exception.ADTEmptyException;

import java.util.List;
import java.util.Stack;

public class MyStack<T> implements MyIStack<T> {

    private final Stack<T> stack;

    public MyStack(){
        this.stack = new Stack<T>();
    }

    @Override
    public T pop() throws ADTEmptyException {
        if(stack.isEmpty())
            throw new ADTEmptyException("Stack is empty");
        return this.stack.pop();
    }

    @Override
    public void push(T v){
        this.stack.push(v);
    }

    @Override
    public boolean isEmpty(){
        return this.stack.isEmpty();
    }

    @Override
    public String toString(){
        return this.stack.toString();
    }

    @Override
    public List<T> getAll() {
        return this.stack.subList(0,stack.size());
    }

    public int size(){
        return this.stack.size();
    }
}
