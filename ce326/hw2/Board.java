package ce326.hw2;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class Board {
    private int rows;
    private int columns;
    private int init_energy;
    private int shield = 0;
    private String[] alphabet = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    private Position[][] gameboard = {};
    private static final String RESET = "\u001b[0m";
    private static final String RED = "\u001b[31m";
    private static final String GREEN = "\u001b[32m";
    private static final String YELLOW = "\u001b[33m";
    private static final String BLUE = "\u001b[34m";

    public Board(int rows, int columns) {
        this.rows = rows;
        this.columns = columns;
        this.gameboard = new Position[rows][columns];
    }

    public void AddToBoard(int row, int column, BoardElement ObjToAdd) {
        this.gameboard[row][column].addContent(ObjToAdd);
    }

    public Position getCell(int row, int column) {
       return(this.gameboard[row][column]);
    }

    public void SetEnergy(int energy) {
        this.init_energy = energy;
    }

    public void SetShield(int shield) {
        this.shield = shield;
    }

    public int GetRows() {
        return this.rows;
    }

    public int GetColumns() {
        return this.columns;
    }

    public int GetEnergy() {
        return this.init_energy;
    }

    public int GetShield() {
        return this.shield;
    }

    public void PrintBoard() {
        for (int i = -1; i < this.rows ; i++) {
            if (i == -1) {
                System.out.print("  ");
                for (int j = 0; j < this.columns; j++) {
                    System.out.print(j+1 + " ");
                }
                System.out.println();
                continue;
            }
            System.out.print(this.alphabet[i] + " ");
            for (int j = 0; j < this.columns; j++) {
                Position currentPos = this.gameboard[i][j];
                String symbolToPrint = "-"; 

                if (currentPos.isObstacle()) {
                    symbolToPrint = "#";
                } 
                else if (!currentPos.getAllContents().isEmpty()) {
                    symbolToPrint = currentPos.getAllContents().get(0).getSymbol();
                    
                    for (BoardElement element : currentPos.getAllContents()) {
                        String sym = element.getSymbol();
                        if (sym.startsWith("@")) {
                            symbolToPrint = sym;
                        }
                        if (sym.equals("X")) {
                            symbolToPrint = sym;
                            break; 
                        }
                    }
                } 
                else if (currentPos.hasVisited()) {
                    symbolToPrint = " ";
                }

                if (symbolToPrint.length() > 1) {
                    char content = symbolToPrint.charAt(0);
                    char colorChar = symbolToPrint.charAt(1);
                    String colorCode = switch (colorChar) {
                        case 'b' -> BLUE;
                        case 'g' -> GREEN;
                        case 'r' -> RED;
                        case 'y' -> YELLOW;
                        default -> RESET;
                    };
                    System.out.print(colorCode + content + RESET + " ");
                } else {
                    System.out.print(symbolToPrint + " ");
                }
            }
            System.out.println();
        }
    }

    public boolean moveActor(String userInput) {
        boolean legalMove;
        int row, column;

        row = rowMatcher(userInput.charAt(0));
        column = Character.getNumericValue(userInput.charAt(1)) - 1;


        return true;
    }

    private int rowMatcher(char rowChar) {
        int row = 0;

        for (char c = 'a' ; c < rowChar ; c++) {
            row++;
        }
        return row;
    }

    private int[] getActorPosition() {
        int[] position = new int[2];
        for (int i = 0; i < this.rows; i++) {
            for (int j = 0; j < this.columns; j++) {
                Position currentPos = this.gameboard[i][j];
                if (!currentPos.getAllContents().isEmpty()) {
                    for (BoardElement element : currentPos.getAllContents()) {
                        if (element instanceof Actor) {
                            position[0] = i;
                            position[1] = j;
                            return position;
                        }
                    }
                }
            }
        }
        return null; 
    }

    public void printDebugInfo() {
        int [][] debugGrid = new int[this.rows][this.columns];
        int[] actorPosition = getActorPosition();
        for(int i = 0; i < this.rows; i++){
            for (int j = 0; j < this.columns; j++){
                if (this.gameboard[i][j].isObstacle()) {
                    debugGrid[i][j] = -1;
                } else {
                    debugGrid[i][j] = 100;
                }  
            }
        }

        Queue<int[]> queue = new LinkedList<>();
        queue.add(actorPosition);
        debugGrid[actorPosition[0]][actorPosition[1]] = 0;

        int[] x = {0, 0, 1, -1}; // right, left, down, up
        int[] y = {1, -1, 0, 0};

        while (!queue.isEmpty()) {
            int[] current = queue.poll();
            for (int i = 0; i < 4; i++) {
                int newRow = current[0] + x[i];
                int newCol = current[1] + y[i];

                if (newRow >= this.rows) { newRow = 0; }
                if (newRow < 0) { newRow = this.rows - 1; }
                if (newCol >= this.columns) { newCol = 0; }
                if (newCol < 0) { newCol = this.columns - 1; }

                if (debugGrid[newRow][newCol] != -1 && debugGrid[newRow][newCol] > debugGrid[current[0]][current[1]] + 1) {
                    debugGrid[newRow][newCol] = debugGrid[current[0]][current[1]] + 1;
                    queue.add(new int[]{newRow, newCol});
                }
            }
        }

        for (int i = -1; i < this.rows; i++) {
            if (i == -1) {
                System.err.print("   ");
                for (int j = 0; j < this.columns; j++) {
                    System.err.print(j + 1 + "  ");
                }
                System.err.println();
                System.err.print(" ");
                for (int j = 0; j < this.columns; j++) {
                    System.err.print("---");
                }
                System.err.println();
                continue;
            }
            System.err.print(this.alphabet[i] + "  ");
            for (int j = 0; j < this.columns; j++) {
                switch (debugGrid[i][j]) {
                    case -1 -> System.err.print("#  ");
                    case 100 -> System.err.print("?  ");
                    default -> System.err.print(debugGrid[i][j] + "  ");
                }
            }
            System.err.println();
        }
    }

    public ArrayList<Ghost>getGhosts(){
        ArrayList<Ghost> ghosts = new ArrayList<>();

        for (int i = 0; i < this.rows; i++) {
            for (int j = 0; j < this.columns; j++) {
                Position currentPos = this.gameboard[i][j];
                if (!currentPos.getAllContents().isEmpty()) {
                    for (BoardElement element : currentPos.getAllContents()) {
                        if (element instanceof Ghost) {
                            ghosts.add((Ghost) element);
                        }
                    }
                }
            }
        }
        return ghosts;
    }

    public Actor getActor() {
        for (int i = 0; i < this.rows; i++) {
            for (int j = 0; j < this.columns; j++) {
                Position currentPos = this.gameboard[i][j];
                if (!currentPos.getAllContents().isEmpty()) {
                    for (BoardElement element : currentPos.getAllContents()) {
                        if (element instanceof Actor) {
                            return (Actor) element;
                        }
                    }
                }
            }
        }
        return null; 
    }
}
