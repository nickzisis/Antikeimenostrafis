package ce326.hw2;

public class Board {
    private int rows;
    private int columns;
    private int init_energy;
    private int shield = 0;
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
        for (int i = 0; i < rows ; i++) {
            for (int j = 0; j < columns; j++) {
                if (gameboard[i][j].length() > 1) {
                    String content = gameboard[i][j].substring(0);
                    char colorChar = gameboard[i][j].charAt(1);
                    String colorCode = RESET;

                    switch (colorChar) {
                    case 'b': colorCode = BLUE; break;
                    case 'g': colorCode = GREEN; break;
                    case 'r': colorCode = RED; break;
                    case 'y': colorCode = YELLOW; break;
                    default:  colorCode = RESET; break;
                    }

                    System.out.print(colorCode + content + RESET + " ");
                }
                else {
                    String content = gameboard[i][j].substring(0);
                    System.out.print(content + " ");
                }
            }
            System.out.print("\n");
        }
    }
}
