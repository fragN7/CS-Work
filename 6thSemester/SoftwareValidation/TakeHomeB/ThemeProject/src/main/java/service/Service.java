package service;

import javafx.util.Pair;
import java.util.ArrayList;
import java.util.Arrays;

/**
 * Clasa Service
 */
public class Service {

    private ArrayList<Integer> originalAnimalArray;
    private final int mouse = 1;
    private final int cat = 2;
    private final int dog = 3;
    private final int cow = 4;


    public Service(ArrayList<Integer> array) {
        this.originalAnimalArray = array;
    }

    public ArrayList<Pair<Integer, Integer>> findPairs(){

        ArrayList<Pair<Integer, Integer>> pairsList = new ArrayList<>();
        for(int animalIndex = 0; animalIndex < this.originalAnimalArray.size() - 1; animalIndex++){
            Integer first = this.originalAnimalArray.get(animalIndex);
            Integer second = this.originalAnimalArray.get(animalIndex + 1);
            if(first == this.mouse && second == this.cat)
                pairsList.add(new Pair<>(animalIndex, this.cow));
            if(first == this.cat && second == this.mouse)
                pairsList.add(new Pair<>(animalIndex, this.cow));
            if(first == this.cat && second == this.dog)
                pairsList.add(new Pair<>(animalIndex, this.cow));
            if(first == this.dog && second == this.cat)
                pairsList.add(new Pair<>(animalIndex, this.cow));
        }

        return pairsList;
    }

    public void insertCow(int index){
        if(this.originalAnimalArray.isEmpty())
            return;
        this.originalAnimalArray.add(index, this.cow);
    }

    public void beFriends(){
        int updateIndex = 1;
        ArrayList<Pair<Integer, Integer>> pairsList = findPairs();
        for(Pair<Integer, Integer> index : pairsList){
            this.insertCow(index.getKey() + updateIndex);
            updateIndex += 1;
        }
    }

}
