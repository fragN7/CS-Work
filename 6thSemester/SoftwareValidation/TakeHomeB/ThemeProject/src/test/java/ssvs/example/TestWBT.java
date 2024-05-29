package ssvs.example;

import javafx.util.Pair;
import org.junit.jupiter.api.Test;
import service.Service;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.*;

public class TestWBT {
    private Service service;

    @Test
    public void testInsertCowWithinBoundsAndTrueCondition() {
        ArrayList<Integer> originalAnimalArray = new ArrayList<>(Arrays.asList(1, 2, 3, 4, 3, 2, 1, 1, 2, 3, 1));
        service = new Service(originalAnimalArray);

        service.insertCow(2);
        assertEquals(4, originalAnimalArray.get(2), "Cow should be inserted at the specified index");
    }

    @Test
    public void testInsertCowWithinBoundsAndFalseCondition() {
        ArrayList<Integer> originalAnimalArray = new ArrayList<>(Arrays.asList(1, 2, 3, 4, 3, 2, 1, 1, 2, 3, 1));
        service = new Service(originalAnimalArray);

        service.insertCow(0);
        assertEquals(4, originalAnimalArray.get(0), "No cow should be inserted at index 0");
    }

    @Test
    public void testInsertCowOutOfBounds() {
        ArrayList<Integer> originalAnimalArray = new ArrayList<>(Arrays.asList(1, 2, 3, 4, 3, 2, 1, 1, 2, 3, 1));
        service = new Service(originalAnimalArray);

        assertThrows(IndexOutOfBoundsException.class, () -> {
            service.insertCow(20); // Index out of bounds
        });
    }

    @Test
    public void testInsertCowEmptyArray() {
        ArrayList<Integer> originalAnimalArray = new ArrayList<>();
        service = new Service(originalAnimalArray);

        service.insertCow(0);
        assertEquals(0, originalAnimalArray.size(), "No cow should be inserted in an empty array");
    }
}
