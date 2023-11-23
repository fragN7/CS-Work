package Collection.Dictionary;

import Exception.ToyLanguageInterpreterException;

import java.util.Collection;
import java.util.Map;
import java.util.Set;

public interface MyIDictionary<K, V>{
    V get(K key) throws ToyLanguageInterpreterException;
    V put(K key,V value);
    String toString();
    int size();
    boolean containsKey(K name);
    Collection<V> values();
    boolean containsValue(V element);
    Set<K> keySet();
    Set<Map.Entry<K,V>> entrySet();
    void setContent(Set<Map.Entry<K,V>> set);
    K getKey(V value);
    MyIDictionary<K, V> clone_dict();
    boolean isDefined(K key);
    void update(K key, V value);
    V lookup(K key) throws ToyLanguageInterpreterException;

    void delete(K key) throws ToyLanguageInterpreterException;

    Map<K, V> getContent();
}
