import java.util.Arrays;
import java.util.List;

public class Main {
    public static void main(String[] args) {

        List<Integer> nums = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15);
        String res = nums.stream().filter(n -> (n % 3 == 0 || n % 2 == 0)).map(n -> "A" + (n+1) + "B").reduce("", (acc, s) -> acc + s);
        System.out.println(res);

        List<Integer> nums1 = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16);
        int res1 = nums1.stream().filter(n -> n % 4 == 0).map(n -> n + 1).reduce(0, (a, b) -> (a+b) % 2);
        System.out.println(res1);
    }
}