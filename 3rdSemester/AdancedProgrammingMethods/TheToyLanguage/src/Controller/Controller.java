package Controller;

import Exception.ToyLanguageInterpreterException;
import Model.State.ProgramState;
import Model.Value.Value;
import Repository.IRepository;
import Model.Value.RefValue;
import java.io.IOException;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.concurrent.*;
import java.util.stream.Collectors;

public class Controller {

    private final IRepository repo;

    private ExecutorService executor;

    public Controller(IRepository repo){
        this.repo = repo;
    }

    public void addProgram(ProgramState state){
        this.repo.addProgram(state);
    }

    public void executeOneStep(List<ProgramState> programStateList) throws InterruptedException {

        programStateList.forEach(prg -> {
            try {
                this.repo.logPrgStateExec(prg);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        });

        List<Callable<ProgramState>> callList = programStateList.stream()
                .map((ProgramState p) -> (Callable<ProgramState>) (p::executeOneStep)).toList();

        List<ProgramState> newPrgList = this.executor.invokeAll(callList).stream()
                .map(future -> {
                    try {
                        return future.get();
                    } catch (InterruptedException | ExecutionException e) {
                        return null;
                    }
                })
                .filter(Objects::nonNull).toList();

        programStateList.addAll(newPrgList);
        programStateList.forEach(prg -> {
            try {
                this.repo.logPrgStateExec(prg);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        });

        this.repo.setProgramList(programStateList);
    }

    public void executeAllStep() throws InterruptedException, ToyLanguageInterpreterException, IOException {

        this.executor = Executors.newFixedThreadPool(2);
        List<ProgramState> programStateList = this.removeCompletedPrg(this.repo.getProgramList());
        while(programStateList.size() > 0) {

            this.callGarbageCollector(programStateList);
            this.executeOneStep(programStateList);
            programStateList = removeCompletedPrg(this.repo.getProgramList());
        }

        this.executor.shutdownNow();
        this.repo.setProgramList(programStateList);
    }

   public  List<Integer> getAddrFromSymTable(Collection<Value> symTableValues){
        return  symTableValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {
                    RefValue v1 = (RefValue) v; return v1.getAddress();})
                .collect(Collectors.toList());
    }

   public void callGarbageCollector(List<ProgramState> programStates){
       programStates.forEach(
                p-> p.getHeap().setContent(safeGarbageCollector(getAddrFromSymTable(p.getSymbolTable().getContent().values()),
                        p.getHeap().getContent()))
       );
   }

    public Map<Integer, Value> safeGarbageCollector(List<Integer> addressesSymbolTable, Map<Integer, Value> heap){

        return heap.entrySet()
                .stream()
                .filter(e -> addressesSymbolTable.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    public List<ProgramState> removeCompletedPrg(List<ProgramState> inPrgList){
        return inPrgList.stream()
                .filter(ProgramState::isNotCompleted)
                .collect(Collectors.toList());
    }

    public IRepository getRepo() {
        return this.repo;
    }
}
