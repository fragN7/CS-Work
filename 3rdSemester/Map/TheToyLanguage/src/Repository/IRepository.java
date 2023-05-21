package Repository;

import Exception.ToyLanguageInterpreterException;
import Model.State.ProgramState;

import java.io.IOException;
import java.util.List;

public interface IRepository {

    void setProgramList(List<ProgramState> list);

    List<ProgramState> getProgramList();

    /*ProgramState getCurrentState();*/

    void addProgram(ProgramState program);

    void logPrgStateExec(ProgramState program) throws IOException;
}
