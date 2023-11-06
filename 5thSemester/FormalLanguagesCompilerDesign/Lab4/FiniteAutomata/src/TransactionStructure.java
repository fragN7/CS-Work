public class TransactionStructure {
    private String initial;
    private String transaction;
    private String finalValue;

    public TransactionStructure(String initial, String transaction, String finalValue) {
        this.initial = initial;
        this.transaction = transaction;
        this.finalValue = finalValue;
    }

    public String getInitial() {
        return initial;
    }

    public void setInitial(String initial) {
        this.initial = initial;
    }

    public String getTransaction() {
        return transaction;
    }

    public void setTransaction(String transaction) {
        this.transaction = transaction;
    }

    public String getFinalValue() {
        return finalValue;
    }

    public void setFinalValue(String finalValue) {
        this.finalValue = finalValue;
    }

    @Override
    public String toString() {
        return "{" + initial +
                ", " + transaction +
                ", " + finalValue +
                '}';
    }
}
