import java.util.ArrayList;
import java.util.List;

public class ProgramInternalForm {

    private List<HashTable.Cell<String, HashTable.Cell<Integer, Integer>>> tokenPairPosition;
    private List<Integer> types;

    public ProgramInternalForm() {
        this.tokenPairPosition = new ArrayList<>();
        this.types = new ArrayList<>();
    }

    public void insert(HashTable.Cell<String, HashTable.Cell<Integer, Integer>> cell, Integer type){
        this.tokenPairPosition.add(cell);
        this.types.add(type);
    }

    @Override
    public String toString(){
        StringBuilder result = new StringBuilder();
        for(int i = 0; i < Integer.parseInt(this.tokenPairPosition.get(i).getKey().toString()); i++){
            result.append(this.tokenPairPosition.get(i).getKey())
                    .append(" - ")
                    .append(this.tokenPairPosition.get(i).getValue())
                    .append(" -> ")
                    .append(types.get(i))
                    .append("\n");
        }

        return result.toString();
    }
}
