package ssvs.example;

import javafx.util.Pair;
import org.junit.jupiter.api.Test;
import service.Service;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;

public class TestBBT {
    private Service service;

    @Test
    public void testFindPairsWithEmptyArray() {
        ArrayList<Integer> originalAnimalArray = new ArrayList<>();
        service = new Service(originalAnimalArray);
        ArrayList<Pair<Integer, Integer>> resultArray = service.findPairs();
        assertEquals(resultArray, new ArrayList<Pair<Integer, Integer>>());
    }

    @Test
    public void testFindPairsWithOneElementArray() {
        ArrayList<Integer> originalAnimalArray = new ArrayList<>(Arrays.asList(1));
        service = new Service(originalAnimalArray);
        ArrayList<Pair<Integer, Integer>> resultArray = service.findPairs();
        assertEquals(resultArray, new ArrayList<Pair<Integer, Integer>>());
    }

    @Test
    public void testFindPairsWithNoPairs() {
        ArrayList<Integer> originalAnimalArray = new ArrayList<>(Arrays.asList(1, 3, 3, 1));
        service = new Service(originalAnimalArray);
        ArrayList<Pair<Integer, Integer>> resultArray = service.findPairs();
        assertEquals(resultArray, new ArrayList<Pair<Integer, Integer>>());
    }

    @Test
    public void testFindPairsWithPairsPresent() {
        ArrayList<Integer> originalAnimalArray = new ArrayList<>(Arrays.asList(1, 2, 3, 4, 3, 2, 1, 1, 2, 3, 1));
        service = new Service(originalAnimalArray);
        ArrayList<Pair<Integer, Integer>> resultArray = service.findPairs();
        assertEquals(6, resultArray.size(), "Unexpected number of pairs found");
        assertEquals(new Pair<>(0, 4), resultArray.get(0), "Unexpected first pair found");
        assertEquals(new Pair<>(1, 4), resultArray.get(1), "Unexpected second pair found");
        assertEquals(new Pair<>(4, 4), resultArray.get(2), "Unexpected third pair found");
        assertEquals(new Pair<>(5, 4), resultArray.get(3), "Unexpected fourth pair found");
        assertEquals(new Pair<>(7, 4), resultArray.get(4), "Unexpected fifth pair found");
        assertEquals(new Pair<>(8, 4), resultArray.get(5), "Unexpected sixth pair found");
    }

}
