class SymbolTable {
    private static final int SIZE = 32;
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

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < SIZE; i++) {
            result.append("index").append(i).append(": ");
            for (String key : table[i].keys()) {
                result.append(key).append(", ").append(table[i].get(key)).append("| ");
            }
            result.append("\n");
        }
        return result.toString();
    }

}