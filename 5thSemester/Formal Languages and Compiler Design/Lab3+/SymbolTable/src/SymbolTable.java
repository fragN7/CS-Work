import java.util.ArrayList;

class SymbolTable {
    private static final int SIZE = 16;
    private HashTable<String, Object>[] table;

    SymbolTable() {
        table = new HashTable[SIZE];
        for (int i = 0; i < SIZE; i++) {
            table[i] = new HashTable<>();
        }
    }

    private int hash(String key) {
        return Math.abs(key.hashCode()) % SIZE;
    }

    public void put(String key, Object value) {
        int index = hash(key);
        table[index].put(key, value);
    }

    public void printSymbolTable() {
        for (int i = 0; i < SIZE; i++) {
            System.out.print("index" + i + ": ");
            for (String key : table[i].keys()) {
                System.out.print(key + ", " + table[i].get(key) + " ");
            }
            System.out.println();
        }
    }
}