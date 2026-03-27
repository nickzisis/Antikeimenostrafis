package ce326.hw2;

public class Ghost extends BoardElement {
    private GhostMovingStrategy strategy;

    public Ghost(int row, int column, String symbol) {
        super(row, column, symbol);
        if (symbol.charAt(1) == 'y'){
            this.strategy = new RandomMovingStrategy();
        } else {
            this.strategy = new OptimalPathMovingStrategy();
        }
    }

    public int[] NextMove(Board gameBoard, boolean ChasedByActor) {
        return this.strategy.nextMove(gameBoard, ChasedByActor, this.getPosition()[0], this.getPosition()[1]);
    }

    public void setPosition(int row, int column) {
        super.setPosition(row, column);
    }
}      
