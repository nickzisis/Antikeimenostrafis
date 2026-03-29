package  ce326.hw2;

public class GameState{
    Board gameBoard;
    int energy;
    int shield;

    public GameState(Board gameBoard, int energy, int shield) {
        this.gameBoard = gameBoard;
        this.energy = energy;
        this.shield = shield;
    }   

    public int getEnergy() {
        return this.energy;
    }

    public int getShield() {
        return this.shield;
    }
    
    public Board getGameBoard() {
        return this.gameBoard;
    }
}