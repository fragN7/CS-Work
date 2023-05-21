package UserInterface;

import Controller.Controller;
import Model.Expression.*;
import Model.State.ProgramState;
import Model.Statement.*;
import Model.Type.BooleanType;
import Model.Type.IntType;
import Model.Type.RefType;
import Model.Value.BooleanValue;
import Model.Value.IntValue;
import Model.Type.StringType;
import Model.Value.StringValue;
import Repository.IRepository;
import Repository.Repository;


public class Interpreter {
    public static void main(String[] args) {

        IStatement ex1 = new CompoundStatement(new VariableDeclarationStatement("v",new IntType()),
                new CompoundStatement(new AssignStatement("v",new ValueExpression(new StringValue("Not good"))),
                        new PrintStatement(new VariableExpression("v"))));

        ProgramState prg1 = new ProgramState(ex1);
        IRepository repo1 = new Repository("1.txt");
        Controller serv1 = new Controller(repo1);
        serv1.addProgram(prg1);


        IStatement ex2 = new CompoundStatement(new VariableDeclarationStatement("a", new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("b", new IntType()),
                        new CompoundStatement(new AssignStatement("a", new ArithmeticExpression('+', new ValueExpression(new IntValue(2)),
                            new ArithmeticExpression('*', new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5))))),
                                new CompoundStatement(new AssignStatement("b", new ArithmeticExpression('+', new VariableExpression("a"),
                                    new ValueExpression(new IntValue(1)))), new PrintStatement(new VariableExpression("b"))))));

        ProgramState prg2 = new ProgramState(ex2);
        IRepository repo2 = new Repository("2.txt");
        Controller serv2 = new Controller(repo2);
        serv2.addProgram(prg2);

        IStatement ex3 = new CompoundStatement(new VariableDeclarationStatement("a", new BooleanType()),
                new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                        new CompoundStatement(new AssignStatement("a", new ValueExpression(new BooleanValue(true))),
                                new CompoundStatement(new IfStatement(new RelationalExpression(new ValueExpression(new IntValue(4)), (new ValueExpression(new IntValue(5))), "<"),
                                        new AssignStatement("v", new ValueExpression(
                                            new IntValue(2))), new AssignStatement("v", new ValueExpression(new IntValue(3)))),
                                                new PrintStatement(new VariableExpression("v"))))));

        ProgramState prg3 = new ProgramState(ex3);
        IRepository repo3 = new Repository("3.txt");
        Controller serv3 = new Controller(repo3);
        serv3.addProgram(prg3);

        IStatement ex4 = new CompoundStatement(new VariableDeclarationStatement("varf",new IntType()),new CompoundStatement(
                new AssignStatement("varf",new ValueExpression(new IntValue(4))),new CompoundStatement(
                    new OpenFileStatement(new VariableExpression("varf")),new CompoundStatement(
                        new VariableDeclarationStatement("varc",new IntType()),new CompoundStatement(
                            new ReadFileStatement(new VariableExpression("varf"),"varc"),new CompoundStatement(
                                new PrintStatement(new VariableExpression("varc")),new CompoundStatement(
                                    new ReadFileStatement(new VariableExpression("varf"),"varc") ,
                                        new CompoundStatement(new PrintStatement(new VariableExpression("varc")),
                                                new CloseFileStatement(new VariableExpression("varf"))))))))));

        ProgramState prg4 = new ProgramState(ex4);
        IRepository repo4 = new Repository("4.txt");
        Controller serv4 = new Controller(repo4);
        serv4.addProgram(prg4);

        IStatement ex5 = new CompoundStatement(new VariableDeclarationStatement("v", new RefType(new IntType())), new CompoundStatement(
                    new NewStatement("v", new ValueExpression(new IntValue(20))),
                        new CompoundStatement(new PrintStatement(new HeapReadExpression(new VariableExpression("v"))), new CompoundStatement(
                            new VariableDeclarationStatement("a", new RefType(new RefType(new IntType()))), new CompoundStatement(
                                new NewStatement("a", new VariableExpression("v")), new CompoundStatement(
                                    new HeapWriteStatement("v", new ValueExpression(new IntValue(30))),
                                        new PrintStatement(new ArithmeticExpression('+', new HeapReadExpression(
                                            new HeapReadExpression(new VariableExpression("a"))), new ValueExpression(new IntValue(5))))))))));

        ProgramState prg5 = new ProgramState(ex5);
        IRepository repo5 = new Repository("5.txt");
        Controller serv5 = new Controller(repo5);
        serv5.addProgram(prg5);

        IStatement ex6 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                    new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(10))),
                        new WhileStatement(new RelationalExpression(new VariableExpression("v"), new ValueExpression(new IntValue(0)), ">"),
                            new CompoundStatement(new PrintStatement(new VariableExpression("v")), new AssignStatement("v",
                                new ArithmeticExpression('-', new VariableExpression("v"), new ValueExpression(new IntValue(1))))))));

        ProgramState prg6 = new ProgramState(ex6);
        IRepository repo6 = new Repository("6.txt");
        Controller serv6 = new Controller(repo6);
        serv6.addProgram(prg6);

        IStatement forkedStatement = new CompoundStatement(new HeapWriteStatement("a",
                new ValueExpression(new IntValue(30))), new CompoundStatement(new AssignStatement("v",
                    new ValueExpression(new IntValue(32))), new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                        new PrintStatement(new HeapReadExpression(new VariableExpression("a"))))));


        IStatement ex7 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new VariableDeclarationStatement("a",new RefType(new IntType())),
                        new CompoundStatement(new AssignStatement("v",new ValueExpression(new IntValue(10))),
                                new CompoundStatement(new NewStatement("a",new ValueExpression(new IntValue(22))),
                                        new CompoundStatement(new ForkStatement(forkedStatement), new CompoundStatement(new PrintStatement(
                                                new VariableExpression("v")),new PrintStatement(new HeapReadExpression(
                                                        new VariableExpression("a")))))))));

        ProgramState prg7 = new ProgramState(ex7);
        IRepository repo7 = new Repository("7.txt");
        Controller serv7 = new Controller(repo7);
        serv7.addProgram(prg7);

        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));
        menu.addCommand(new RunExample("1", ex1.toString(), serv1));
        menu.addCommand(new RunExample("2", ex2.toString(), serv2));
        menu.addCommand(new RunExample("3", ex3.toString(), serv3));
        menu.addCommand(new RunExample("4", ex4.toString(), serv4));
        menu.addCommand(new RunExample("5", ex5.toString(), serv5));
        menu.addCommand(new RunExample("6", ex6.toString(), serv6));
        menu.addCommand(new RunExample("7", ex7.toString(), serv7));
        menu.show();
    }
}
