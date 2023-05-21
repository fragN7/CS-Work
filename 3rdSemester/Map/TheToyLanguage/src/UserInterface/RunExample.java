package UserInterface;

import Collection.Dictionary.MyDictionary;
import Controller.Controller;

import Exception.ToyLanguageInterpreterException;
import Model.Type.Type;

import java.io.IOException;

public class RunExample extends Command{

    private final Controller service;

    public RunExample(String key, String desc, Controller service){
        super(key, desc);
        this.service = service;
    }

    @Override
    public void execute() {
        try{
            this.service.getRepo().getProgramList().get(0).getExecutionStack().getAll().get(0).typecheck(new MyDictionary<String, Type>());
            this.service.executeAllStep();
        } catch (ToyLanguageInterpreterException | InterruptedException | IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
