import java.util.ArrayList;
import java.util.List;

public class ProgramInternalForm {

    private List<HashTable.Cell<String, List<Integer>>> tokenPairPosition;
    private List<Integer> types;

    public ProgramInternalForm() {
        this.tokenPairPosition = new ArrayList<>();
        this.types = new ArrayList<>();
    }

    public <V, K> void insert(HashTable.Cell<K, V> kvCell, int type) {
        String key = kvCell.getKey().toString();
        List<Integer> value = List.of(kvCell.getValue().toString().hashCode());
        tokenPairPosition.add(new HashTable.Cell<>(key, value));
        types.add(type);
    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder();
        for (int i = 1; i < tokenPairPosition.size(); i++) {
            HashTable.Cell<String, List<Integer>> cell = tokenPairPosition.get(i);
            result.append(cell.getKey()).append(" - ");
            List<Integer> value = cell.getValue();
            for (Integer val : value) {
                result.append(val).append(" ");
            }
            result.append(" -> ").append(types.get(0)).append("\n");
        }
        return result.toString();
    }
}
