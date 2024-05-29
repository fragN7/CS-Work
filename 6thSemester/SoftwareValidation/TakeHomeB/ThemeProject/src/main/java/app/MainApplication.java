package app;
import service.Service;

import java.util.ArrayList;
import java.util.Arrays;


public class MainApplication {

    public static void main(String[] args) {

        ArrayList<Integer> originalAnimalArray = new ArrayList<>(Arrays.asList(1, 2, 3, 4, 3, 2, 1, 1, 2, 3, 1));
        Service service = new Service(originalAnimalArray);


    }

}
