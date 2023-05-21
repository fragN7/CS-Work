import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) {
        List list = new ArrayList();
        list.add("one");
        list.add("two");
        list.add(9);
        for(Object s : list)
            System.out.println(s);

        List<Integer> numbers1 = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14,15);
        String result1 = numbers1.stream()
                .filter(n -> n % 2 == 0 || n % 3 == 0)
                .map(n -> String.format("B%dR", n))
                .collect(Collectors.joining());

        System.out.println(result1);

        List<Integer> result2 = numbers1.stream()
                .filter(n -> n % 4 == 0)
                .toList();

        List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15);

        Integer sumModulo5 = numbers.stream()
                .filter(n -> n % 3 == 0 || n % 7 == 0)
                .map(n -> n - 1)
                .mapToInt(Integer::intValue)
                .sum() % 5;

        System.out.println(sumModulo5);

        Amain m = new Amain();
        A el = new A();
        m.method3(el);

    }
}

class A{

    A(){};
}

class B extends A{

    B(){};
}

class C extends A{

    C(){};
}

class Amain{

    A method1(List<? extends A> list) { return list.get(1);}
    void method2(List<A> list, A el) { list.add(el);}
    void method3(A elem){
        ArrayList<A> listA=new ArrayList<A>(); listA.add(new B());listA.add(new C());
        ArrayList<B> listB = new ArrayList<B>(); listB.add(new B());listB.add(new B());
        ArrayList<C> listC = new ArrayList<C>(); listC.add(new C());listC.add(new C());

        this.method1(listA); this.method1(listB); this.method1(listC);
    }


}