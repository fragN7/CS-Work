package ssvs.example;

import javafx.util.Pair;
import org.junit.jupiter.api.Test;
import service.Service;

import java.util.ArrayList;
import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.*;

public class TestIntegration {
    private Service service;

    @Test
    public void testBeFriendsWithEmptyArray() {
        ArrayList<Integer> originalAnimalArray = new ArrayList<>();
        service = new Service(originalAnimalArray);

        service.beFriends();

        assertEquals(originalAnimalArray, new ArrayList<>(), "Empty array should remain unchanged");
    }

    @Test
    public void testBeFriendsWithSingleAnimal() {
        ArrayList<Integer> originalAnimalArray = new ArrayList<>(Arrays.asList(1));
        service = new Service(originalAnimalArray);

        service.beFriends();

        assertEquals(originalAnimalArray, Arrays.asList(1), "Array with single animal should remain unchanged");
    }

    @Test
    public void testBeFriendsWithNoPairs() {
        ArrayList<Integer> originalAnimalArray = new ArrayList<>(Arrays.asList(1, 3, 3, 1));
        service = new Service(originalAnimalArray);

        service.beFriends();

        assertEquals(originalAnimalArray, Arrays.asList(1, 3, 3, 1), "Array with no pairs should remain unchanged");
    }

    @Test
    public void testBeFriendsWithMultiplePairs() {
        ArrayList<Integer> originalAnimalArray = new ArrayList<>(Arrays.asList(1, 2, 3, 4, 3, 2, 1, 1, 2, 3, 1));
        service = new Service(originalAnimalArray);

        service.beFriends();
        assertEquals(originalAnimalArray, Arrays.asList(1, 4, 2, 4, 3, 4, 3, 4, 2, 4, 1, 1, 4, 2, 4, 3, 1));
    }
}
