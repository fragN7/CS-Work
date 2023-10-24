import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.StringTokenizer;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

public class Scanner {

    private final ArrayList<String> operators = new ArrayList<>(
            List.of("+", "-", "*", "%", "/", "<=", ">=", "=", "<>", ">", "<", "<-", "<+")
    );

    private final ArrayList<String> separators = new ArrayList<>(
      List.of("{", "}", "(", ")", "[", "]", ":", ";", ",", "\n" ," ")
    );

    private final ArrayList<String> reservedWords = new ArrayList<>(
      List.of("Perhaps", "Between", "Enter", "Leave", "InBetween", "num", "str", "bol")
    );

    private String filePath;

    private SymbolTable symbolTable;

    private ProgramInternalForm pif;


    public Scanner(String filePath) {
        this.filePath = filePath;
        this.symbolTable = new SymbolTable();
        this.pif = new ProgramInternalForm();
    }

    private String readFile() throws FileNotFoundException {
        StringBuilder fileContent = new StringBuilder();
        Scanner scanner = new Scanner(new File(this.filePath));

        return fileContent.toString().replace("\t", "");
    }

    private List<HashTable.Cell<String, HashTable.Cell<Integer, Integer>>> createListOfProgramsElems(){
        try{
            String content = this.readFile();
            String separatorsString = this.separators.stream().reduce("", (a,b)->(a + b));
            StringTokenizer tokenizer = new StringTokenizer(content, separatorsString, true);

            List<String> tokens = Collections.list(tokenizer)
                    .stream()
                    .map(t->(String) t)
                    .collect(Collectors.toList());

            return tokenize(tokens);
        }
        catch (FileNotFoundException e){
            e.printStackTrace();
        }

        return null;
    }

    private List<HashTable.Cell<String, HashTable.Cell<Integer, Integer>>> tokenize(List<String> tokensToBe){

        List<HashTable.Cell<String, HashTable.Cell<Integer, Integer>>> resultedTokens = new ArrayList<>();
        boolean isStringConstant = false;
        boolean isCharConstant = false;
        StringBuilder createdString = new StringBuilder();
        int numberLine = 1;
        int numberColumn = 1;

        for(String t: tokensToBe){
            switch (t) {
                case "\"":
                    if (isStringConstant) {
                        createdString.append(t);
                        resultedTokens.add(new HashTable.Cell<>(createdString.toString(), new HashTable.Cell<>(numberLine, numberColumn)));
                        createdString = new StringBuilder();
                    }else {
                        createdString.append(t);
                    }
                    isStringConstant = !isStringConstant;
                    break;
                case "'":
                    if (isCharConstant) {
                        createdString.append(t);
                        resultedTokens.add(new HashTable.Cell<>(createdString.toString(), new HashTable.Cell<>(numberLine, numberColumn)));
                        createdString = new StringBuilder();
                    }
                    else {
                        createdString.append(t);
                    }
                    isCharConstant = !isCharConstant;
                    break;
                case "\n":
                    numberLine++;
                    numberColumn = 1;
                    break;
                default:
                    if (isStringConstant) {
                        createdString.append(t);
                    } else if (isCharConstant) {
                        createdString.append(t);
                    } else if (!t.equals(" ")) {
                        resultedTokens.add(new HashTable.Cell<>(t, new HashTable.Cell<>(numberLine, numberColumn)));
                        numberColumn++;
                    }
                    break;
            }
        }
        return resultedTokens;
    }

    public void scan(){

        List<HashTable.Cell<String, HashTable.Cell<Integer, Integer>>> tokens = createListOfProgramsElems();
        AtomicBoolean lexicalErrorExists = new AtomicBoolean(false);

        if(tokens == null){
            return;
        }

        tokens.forEach(t -> {
            String token = t.getKey();
            if(this.reservedWords.contains(token)) {
                this.pif.insert(new HashTable.Cell<>(token, new HashTable.Cell<>(-1, -1)), 2);
            } else if(this.operators.contains(token)){
                this.pif.insert(new HashTable.Cell<>(token, new HashTable.Cell<>(-1, -1)), 3);
            } else if(this.separators.contains(token)){
                this.pif.insert(new HashTable.Cell<>(token, new HashTable.Cell<>(-1, -1)), 4);
            } else if(Pattern.compile("^0|[-| ][1-9]([0-9])*|'[1-9]'|'[a-zA-Z]'|\"[0-9]*[a-zA-Z ]*\"$").matcher(token).matches()) {
                this.symbolTable.add(token);
                this.pif.insert(new HashTable.Cell<>("CONST", symbolTable.findPositionOfTerm(token)), 0);
//                this.pif.add(new Pair<>("const", symbolTable.findPositionOfTerm(token)), 0);
            }
            else if(Pattern.compile("^([a-zA-Z]|_)|[a-zA-Z_0-9]*").matcher(token).matches()) {
                this.symbolTable.add(token);
                this.pif.insert(new HashTable.Cell<>("IDENTIFIER", symbolTable.findPositionOfTerm(token)), 1);
//                this.pif.add(new Pair<>("ident", symbolTable.findPositionOfTerm(token)), 1);
            } else {
                HashTable.Cell<Integer, Integer> pairLineColumn = t.getValue();
                System.out.println("Error at line: " + pairLineColumn.getKey() + " and column: " + pairLineColumn.getValue() + ", invalid token: " + t.getKey());
                lexicalErrorExists.set(true);
            }
        });

        if(!lexicalErrorExists.get()){
            System.out.println("Program is lexically correct!");
        }

    }

    public ProgramInternalForm getPif(){
        return this.pif;
    }

    public SymbolTable getSymbolTable() {
        return this.symbolTable;
    }
}
