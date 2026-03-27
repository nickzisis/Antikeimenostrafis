package ce326.hw2;

public abstract class BoardElement {
    private int[] position = new int[2];
    private String symbol;

    public BoardElement(int row, int column, String symbol) {
        this.position[0] = row;
        this.position[1] = column;
        this.symbol= symbol;
    }

    public String getSymbol() {
        return this.symbol;
    }
}   