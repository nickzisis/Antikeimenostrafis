package ce326.hw2;

import java.util.ArrayList;

public class Position {
    private int row;
    private int column;
    private ArrayList<BoardElement> content;
    private boolean hasVisited;
    private boolean isObstacle;

    public Position(int row, int column, boolean isObstacle) {
        this.row = row;
        this.column = column;
        this.isObstacle = isObstacle;
        this.hasVisited = false;
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

    public ArrayList<BoardElement> getAllContents() {
        return this.content;
    }

    public void setObstacle(boolean isObstacle) {
        this.isObstacle = isObstacle;
    }

    public boolean isObstacle() {
        return this.isObstacle;
    }

    public boolean hasGhost() {
        for (BoardElement element : this.content) {            
            if (element instanceof Ghost) { 
                return true; 
            }
        }
        return false;
    }

    public boolean hasActor() {
        for (BoardElement element : this.content) {            
            if (element instanceof Actor) { 
                return true; 
            }
        }
        return false;
    }

    public void setVisited(boolean visited) {
        this.hasVisited = visited;
    }
    
    public boolean hasVisited() {
        return this.hasVisited;
    }
}
