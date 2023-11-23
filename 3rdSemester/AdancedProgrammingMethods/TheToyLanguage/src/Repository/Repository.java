package Repository;

import Model.State.ProgramState;

import java.io.IOException;
import java.io.PrintWriter;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository{

    private List<ProgramState> programStates;
    private final int currentPosition;
    private final String logFilePath;

    public Repository(String logFilePath){
        this.programStates = new ArrayList<>();
        this.currentPosition = 0;
        this.logFilePath = logFilePath;
    }

    @Override
    public void addProgram(ProgramState program){
        this.programStates.add(program);
    }

    @Override
    public void logPrgStateExec(ProgramState program) throws IOException {
        PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(this.logFilePath, true)));
        logFile.write(this.programStates.toString());
        logFile.close();
    }

    @Override
    public void setProgramList(List<ProgramState> list) {
        this.programStates = list;
    }

    @Override
    public List<ProgramState> getProgramList() {
        return programStates;
    }

    /*@Override
    public ProgramState getCurrentState(){
        return this.programStates.get(this.currentPosition);
    }*/
}
