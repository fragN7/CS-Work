public class Main {
    public static void main(String[] args) {
        SymbolTable st = new SymbolTable();

        st.put("variable1", 10);
        st.put("variable2", "Hello");
        st.put("'PI'", 3.14);
        st.put("'G'", 9.81);

        st.printSymbolTable();
    }
}