package Model.Statement;

import Collection.Dictionary.MyIDictionary;
import Exception.StatementExecutionException;
import Exception.ToyLanguageInterpreterException;
import Model.State.ProgramState;
import Model.Type.Type;
import Model.Value.Value;


public class VariableDeclarationStatement implements IStatement{

    private final String name;

    private final Type type;

    public VariableDeclarationStatement(String name, Type type){
        this.type = type;
        this.name = name;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ToyLanguageInterpreterException {
        MyIDictionary<String, Value> symbolTable = state.getSymbolTable();
        if (symbolTable.containsKey(this.name)){
            throw new StatementExecutionException("Variable " + this.name + " already exists.");
        }
        symbolTable.put(this.name, this.type.defaultValue());
        state.setSymbolTable(symbolTable);
        return null;
    }

    @Override
    public String toString() {
        return String.format("%s %s", this.type.toString(), this.name);
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws ToyLanguageInterpreterException {
         typeEnv.put(this.name, this.type);
         return typeEnv;
    }
}
