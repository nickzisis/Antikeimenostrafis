package ce326.hw2;

public class Board {
    private int rows;
    private int columns;
    private int init_energy;
    private int shield = 0;
    private String[] alphabet = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    private String[][] gameboard = {};
    private static final String RESET = "\u001b[0m";
    private static final String RED = "\u001b[31m";
    private static final String GREEN = "\u001b[32m";
    private static final String YELLOW = "\u001b[33m";
    private static final String BLUE = "\u001b[34m";

    public Board(int rows, int columns) {
        this.rows = rows;
        this.columns = columns;
        this.gameboard = new String[rows][columns];
    }

    public void AddToBoard(int row, int column, String ObjToAdd) {
        this.gameboard[row][column] = ObjToAdd;
    }

    public String getCell(int row, int column) {
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
                if (gameboard[i][j].length() > 1) {
                    char content = gameboard[i][j].charAt(0);
                    char colorChar = gameboard[i][j].charAt(1);
                    String colorCode = switch (colorChar) {
                        case 'b' -> BLUE;
                        case 'g' -> GREEN;
                        case 'r' -> RED;
                        case 'y' -> YELLOW;
                        default -> RESET;
                    };
                    System.out.print(colorCode + content + RESET + " ");
                }
                else {
                    char content = gameboard[i][j].charAt(0);
                    System.out.print(content + " ");
                }
            }
            System.out.println();
        }
    }
}
