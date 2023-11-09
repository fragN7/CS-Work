import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;

public class FA {

    private final List<String> states = new ArrayList<>();
    private final List<String> alphas = new ArrayList<>();
    private String initialState;
    private final List<String> finalStates = new ArrayList<>();

    private final List<TransactionStructure> transactions = new ArrayList<>();
    private final Map<String, List<String>> transactionGraph  = new HashMap<>();
    private final String filePath;

    public FA(String filePath){
        this.filePath = filePath;
        this.readFromFile();
    }

    public void readFromFile(){
        try {
            List<String> lines = Files.readAllLines(Paths.get(filePath));
            for (String line : lines) {
                if (line.startsWith("states: ")) {
                    String[] statesArray = line.substring(8).split(", ");
                    Collections.addAll(states, statesArray);
                } else if (line.startsWith("alphas: ")) {
                    String[] alphasArray = line.substring(8).split(", ");
                    Collections.addAll(alphas, alphasArray);
                } else if (line.startsWith("initial state: ")) {
                    initialState = line.substring(15);
                } else if (line.startsWith("final states: ")) {
                    String[] finalStatesArray = line.substring(14).split(", ");
                    Collections.addAll(finalStates, finalStatesArray);
                } else if (line.startsWith("transactions: ")) {
                    String[] transactionsArray = line.substring(14).split(" \\| ");
                    for (String transaction : transactionsArray) {
                        String[] parts = transaction.split(", ");
                        transactions.add(new TransactionStructure(parts[0], parts[1], parts[2]));
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public String transactionResult(String transactions){
        String[] transactionList = transactions.split("\\s+");
        String currentState = this.initialState;

        for (String transaction: transactionList) {

            if(!this.alphas.contains(transaction))
                return "Alpha " + transaction + " not in transaction list";

            boolean validTransaction = false;
            for (TransactionStructure trs: this.transactions) {
                if(trs.getTransaction().equals(transaction) && trs.getInitial().equals(currentState)){
                    currentState = trs.getFinalValue();
                    validTransaction = true;
                    break;
                }
            }

            if(!validTransaction)
                return "Invalid transaction sequence";
        }

        if(this.finalStates.contains(currentState))
            return "Valid transaction sequence";
        else
            return "Transaction sequence does not end in a final state";
    }

    public void displayStates(){
        System.out.println("\nStates: ");
        for (String state: states) {
            System.out.println(state);
        }
    }

    public void displayAlphas(){
        System.out.println("\nAlphas: ");
        for (String alpha: alphas) {
            System.out.println(alpha);
        }
    }
    public void displayTransactions(){
        System.out.println("\nTransactions: ");
        for (TransactionStructure transaction: transactions) {
            System.out.println(transaction);
        }
    }
    public void displayInitialState(){
        System.out.println("\nInitial State: ");
        System.out.println(this.initialState);
    }
    public void displayFinalStates(){
        System.out.println("\nFinal States: ");
        for (String state: finalStates) {
            System.out.println(state);
        }
    }

}
