import java.util.LinkedList;

class HashTable<K, V> {
    private static final int SIZE = 32;
    private LinkedList<Cell<K, V>>[] table;

    HashTable() {
        table = new LinkedList[SIZE];
        for (int i = 0; i < SIZE; i++) {
            table[i] = new LinkedList<>();
        }
    }

    void put(K key, V value) {
        int index = Math.abs(key.hashCode()) % SIZE;
        LinkedList<Cell<K, V>> list = table[index];
        for (Cell<K, V> cell : list) {
            if (cell.getKey().equals(key)) {
                cell.setValue(value);
                return;
            }
        }
        list.add(new Cell<>(key, value));
    }

    V get(K key) {
        int index = Math.abs(key.hashCode()) % SIZE;
        LinkedList<Cell<K, V>> list = table[index];
        for (Cell<K, V> cell : list) {
            if (cell.getKey().equals(key)) {
                return cell.getValue();
            }
        }
        return null;
    }

    Iterable<K> keys() {
        LinkedList<K> keys = new LinkedList<>();
        for (LinkedList<Cell<K, V>> list : table) {
            for (Cell<K, V> cell : list) {
                keys.add(cell.getKey());
            }
        }
        return keys;
    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder();
        for (LinkedList<Cell<K, V>> list : table) {
            for (Cell<K, V> cell : list) {
                result.append(cell.getKey()).append(" => ").append(cell.getValue()).append("\n");
            }
        }
        return result.toString();
    }

    public static class Cell<K, V> {
        private final K key;
        private V value;

        Cell(K key, V value) {
            this.key = key;
            this.value = value;
        }

        K getKey() {
            return key;
        }

        V getValue() {
            return value;
        }

        void setValue(V value) {
            this.value = value;
        }

        @Override
        public String toString() {
            return key + " => " + value;
        }
    }
}