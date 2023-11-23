package UserInterface;

import java.util.Map;
import java.util.Scanner;
import java.util.HashMap;

public class TextMenu {

    private final Map<String, Command> cmds;

    public TextMenu() {
        this.cmds = new HashMap<>();
    }

    public void addCommand(Command cmd){
        this.cmds.put(cmd.getKey(), cmd);
    }

    private void printMenu(){
        for (Command cmd: this.cmds.values()){
            String line = String.format("%4s : %s", cmd.getKey(), cmd.getDesc());
            System.out.println(line);
        }
    }

    public void show() {
        Scanner keyboard = new Scanner(System.in);
        System.out.println(">>>");

        while (true){
            this.printMenu();
            System.out.println(">>>");
            String key = keyboard.nextLine();
            Command cmd = this.cmds.get(key);
            if(cmd == null){
                System.out.println("Invalid option!");
                continue;
            }

            cmd.execute();
        }

    }
}
