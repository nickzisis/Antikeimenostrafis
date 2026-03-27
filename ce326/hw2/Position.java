package ce326.hw2;

import java.util.ArrayList;

public class Position {
    private int row;
    private int column;
    private ArrayList<BoardElement> content;
    private boolean HasVisited;
    private boolean IsObstacle;

    public Position(int row, int column, boolean isObstacle) {
        this.row = row;
        this.column = column;
        this.IsObstacle = isObstacle;
        this.HasVisited = false;
        this.content = new ArrayList<>();
    }

    public void addContent(BoardElement obj) {
        this.content.add(obj);
    }

    public void removeContent(BoardElement obj) {
        this.content.remove(obj);
    }

    public int getRow() {
        return this.row;
    }

    public int getColumn() {
        return this.column;
    }   


}
