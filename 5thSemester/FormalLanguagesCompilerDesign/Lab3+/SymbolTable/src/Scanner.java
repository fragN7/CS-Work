import java.io.*;
import java.util.*;

public class Scanner {
    private final SymbolTable symbolTable;
    private final ProgramInternalForm pif;
    private final ArrayList<String> operators;
    private final ArrayList<String> separators;
    private final ArrayList<String> reservedWords;

    public Scanner() {
        this.symbolTable = new SymbolTable();
        this.pif = new ProgramInternalForm();
        this.operators = new ArrayList<>(List.of("+", "-", "*", "%", "/", "<=", ">=", "=", "<>", ">", "<", "<-", "<+"));
        this.separators = new ArrayList<>(List.of("{", "}", "(", ")", "[", "]", ":", ";", ",", "\n", " "));
        this.reservedWords = new ArrayList<>(List.of("Perhaps", "Between", "Enter", "Leave", "InBetween", "num", "str", "bol", "met", "inv", "GetOut"));
    }

    public void scanFile(String filePath) {
        try (BufferedReader br = new BufferedReader(new FileReader(filePath));
             BufferedWriter pifWriter = new BufferedWriter(new FileWriter("PIF.out"));
             BufferedWriter stWriter = new BufferedWriter(new FileWriter("ST.out"));
             BufferedWriter outputWriter = new BufferedWriter(new FileWriter("OUT.out"))) {

            int position = 0;
            int currentInt;

            while ((currentInt = br.read()) != -1) {
                char currentChar = (char) currentInt;
                if (isSeparator(currentChar)) {
                    if (!Character.isWhitespace(currentChar)) {
                        processToken(String.valueOf(currentChar), position);
                    }
                    position++;
                } else if (isOperator(String.valueOf(currentChar))) {
                    processToken(String.valueOf(currentChar), position);
                    position++;
                } else {
                    StringBuilder currentToken = new StringBuilder();
                    currentToken.append(currentChar);
                    int nextInt;
                    while ((nextInt = br.read()) != -1) {
                        char nextChar = (char) nextInt;
                        if (isSeparator(nextChar) || isOperator(String.valueOf(nextChar)) || Character.isWhitespace(nextChar)) {
                            processToken(currentToken.toString(), position);
                            position++;
                            if (!Character.isWhitespace(nextChar)) {
                                processToken(String.valueOf(nextChar), position);
                                position++;
                            }
                            break;
                        } else {
                            currentToken.append(nextChar);
                        }
                    }
                    if (nextInt == -1) {
                        processToken(currentToken.toString(), position);
                    }
                }
            }

            stWriter.write(symbolTable.toString());
            pifWriter.write(pif.toString());
            outputWriter.write("Lexically correct");

        } catch (Exception e) {
            try (BufferedWriter outputWriter = new BufferedWriter(new FileWriter("OUT.out"))) {
                outputWriter.write("Lexically incorrect: " + e.getMessage());
            } catch (Exception ioException) {
                ioException.printStackTrace();
            }
        }
    }

    private void processToken(String token, int position) {
        if (isReservedWord(token)) {
            symbolTable.put(token, "ReservedWord");
            pif.insert(new HashTable.Cell<>(new HashTable.Cell<>(position, position + token.length() - 1), 0), 0);
        } else if (isOperator(token)) {
            symbolTable.put(token, "Operator");
            pif.insert(new HashTable.Cell<>(new HashTable.Cell<>(position, position), 1), 1);
        } else if (isSeparator(token.charAt(0))) {
            if (token.equals("(")) {
                String constant = extractStringConstant(token, position);
                symbolTable.put(constant, "StringConstant");
                pif.insert(new HashTable.Cell<>(new HashTable.Cell<>(position, position + constant.length() + 1), 4), 4);
            } else {
                symbolTable.put(token, "Separator");
                pif.insert(new HashTable.Cell<>(new HashTable.Cell<>(position, position), 2), 2);
            }
        } else {
            symbolTable.put(token, "Identifier");
            pif.insert(new HashTable.Cell<>(new HashTable.Cell<>(position, position + token.length() - 1), 3), 3);
        }
    }

    private String extractStringConstant(String token, int position) {
        StringBuilder constantBuilder = new StringBuilder();
        constantBuilder.append(token.substring(1));
        for (int i = 0; i < token.length(); i++) {
            char currentChar = token.charAt(i);
            if (currentChar == ')') {
                constantBuilder.append(currentChar);
                break;
            } else {
                constantBuilder.append(currentChar);
            }
        }
        return constantBuilder.toString();
    }

    private boolean isOperator(String token) {
        return operators.contains(token);
    }

    private boolean isSeparator(char c) {
        return separators.contains(String.valueOf(c));
    }

    private boolean isReservedWord(String token) {
        return reservedWords.contains(token);
    }
}