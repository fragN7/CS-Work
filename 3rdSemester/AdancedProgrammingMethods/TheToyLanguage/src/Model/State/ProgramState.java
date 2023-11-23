package Model.State;

import Collection.Dictionary.MyDictionary;
import Collection.Dictionary.MyIDictionary;
import Collection.Heap.MyHeap;
import Collection.Heap.MyIHeap;
import Collection.List.MyIList;
import Collection.List.MyList;
import Collection.Stack.MyIStack;
import Collection.Stack.MyStack;
import Model.Statement.IStatement;
import Model.Value.Value;
import Exception.ToyLanguageInterpreterException;

import java.io.BufferedReader;
import java.io.IOException;

public class ProgramState {
    private MyIStack<IStatement> executionStack;
    private MyIDictionary<String, Value> symbolTable;
    private MyIList<Value> outputList;

    private MyIDictionary<String, BufferedReader> fileTable;

    private MyIHeap<Value> heap;

    private final IStatement originalProgram;

    private int id;
    private static int globalID = 1;

    public ProgramState(MyIStack<IStatement> programStateMyStack, MyIDictionary<String, Value> symbolTable,
                        MyIList<Value> outputList, IStatement originalProgram, MyIHeap<Value> heap,
                        MyIDictionary<String, BufferedReader> fileTable){

        this.executionStack = programStateMyStack;
        this.symbolTable = symbolTable;
        this.outputList = outputList;
        this.originalProgram = originalProgram;
        //this.executionStack.push(originalProgram);
        this.heap = heap;
        this.fileTable = fileTable;
        this.id = this.getGlobalID();
    }

    public ProgramState(IStatement originalProgram){

        this.executionStack = new MyStack<>();
        this.symbolTable = new MyDictionary<>();
        this.outputList = new MyList<Value>();
        this.fileTable = new MyDictionary<String, BufferedReader>();
        this.heap = new MyHeap<>();
        this.originalProgram = originalProgram;
        this.executionStack.push(originalProgram);
        this.id = 1;
    }

    public MyIStack<IStatement> getExecutionStack(){
        return this.executionStack;
    }

    public void setExecutionStack(MyIStack<IStatement> executionStack){
        this.executionStack = executionStack;
    }

    public MyIDictionary<String, Value> getSymbolTable(){
        return this.symbolTable;
    }

    public void setSymbolTable(MyIDictionary<String, Value> symbolTable){
        this.symbolTable = symbolTable;
    }

    public MyIList<Value> getOutputList() {
        return this.outputList;
    }

    public void setOutputList(MyIList<Value> outputList) {
        this.outputList = outputList;
    }

    public MyIHeap<Value> getHeap() {
        return this.heap;
    }

    public void setHeap(MyIHeap<Value> heap) {
        this.heap = heap;
    }

    public MyIDictionary<String, BufferedReader> getFileTable() {
        return this.fileTable;
    }

    public  Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public synchronized int getGlobalID()
    {
        globalID += 1;
        return globalID;
    }

    public boolean isNotCompleted(){
        return !this.executionStack.isEmpty();
    }

    public ProgramState executeOneStep() throws ToyLanguageInterpreterException, IOException {

        if(this.executionStack.isEmpty())
            throw new ToyLanguageInterpreterException("Program state is empty");
        IStatement controlStatement = this.executionStack.pop();
        return controlStatement.execute(this);
    }

    @Override
    public String toString() {
        return
                "Program State with ID:" + this.id + "\n" +
                "--------------------------------------------------------\n" +
                "Output List:\n" + this.outputList.toString() + "\n" +
                "Symbol Table:\n" + this.symbolTable.toString() + "\n" +
                "Execution Stack:\n" + this.executionStack.toString() + "\n" +
                "File Table:\n" + this.fileTable.toString() + "\n" +
                "Heap Table:\n" + this.heap.toString() + "\n" +
                "--------------------------------------------------------\n";
    }
}
