import java.util.Scanner;

public class Main {

    private void uiDisplayStates(FA fa){
        fa.displayStates();
    }
    private void uiDisplayAlphas(FA fa){
        fa.displayAlphas();
    }
    private void uiDisplayInitialState(FA fa){
        fa.displayInitialState();
    }
    private void uiDisplayFinalStates(FA fa){
        fa.displayFinalStates();
    }
    private void uiDisplayTransactions(FA fa){
        fa.displayTransactions();
    }

    private void uiInputTransaction(FA fa){
        System.out.println("Enter your transaction (t1 t2 t3): ");
        Scanner scanner = new Scanner(System.in);
        String transaction = scanner.nextLine();
        System.out.println(fa.transactionResult(transaction));
    }

    private void displayMenu(){
        System.out.println("Please choose an option:");
        System.out.println("1 - Display states");
        System.out.println("2 - Display alphas");
        System.out.println("3 - Display initial state");
        System.out.println("4 - Display final states");
        System.out.println("5 - Display transactions");
        System.out.println("0 - Exit");
    }

    public void run(FA fa){
        Scanner scanner = new Scanner(System.in);

        this.displayMenu();
        while(true){
            System.out.println("\nYour option: ");
            int opt = scanner.nextInt();
            switch (opt) {
                case 0:
                    System.out.println("Bye!");
                    return;
                case 1:
                    this.uiDisplayStates(fa);
                    break;
                case 2:
                    this.uiDisplayAlphas(fa);
                    break;
                case 3:
                    this.uiDisplayInitialState(fa);
                    break;
                case 4:
                    this.uiDisplayFinalStates(fa);
                    break;
                case 5:
                    this.uiDisplayTransactions(fa);
                    break;
                case 6:
                    this.uiInputTransaction(fa);
                    break;
                default:
                    System.out.println("Invalid option selected");
            }
        }
    }

    public static void main(String[] args) {
        FA fa = new FA("C:\\Users\\Alen\\Documents\\GithubPrivate\\CS-Work\\5thSemester\\FormalLanguagesCompilerDesign\\Lab4\\FiniteAutomata\\FA.in");
        Main main = new Main();
        main.run(fa);
    }
}