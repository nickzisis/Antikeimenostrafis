package ce326.hw2;

import java.util.Random;

public class RandomMovingStrategy implements GhostMovingStrategy{
    
    @Override
    public int[] nextMove(Board gameBoard, boolean ChasedByActor, int startRow, int startColumn) {
        int[] nextMove = new int[2];
        int[] canGo = {0,1,2,3};
        Position content;

        do {
            int rndGo = new Random().nextInt(canGo.length);
            switch (rndGo) {
                case 0 -> {
                    nextMove[0] = startRow + 1;
                    nextMove[1] = startColumn;
                }
                case 1 -> {
                    nextMove[0] = startRow - 1;
                    nextMove[1] = startColumn;
                }
                case 2 -> {
                    nextMove[0] = startRow;
                    nextMove[1] = startColumn + 1;
                }
                case 3 -> {
                    nextMove[0] = startRow;
                    nextMove[1] = startColumn - 1;
                }
                default -> {
                }
            }
            
            if (nextMove[0] < 0) {
                nextMove[0] = gameBoard.GetRows() - 1;;
            }
            if (nextMove[0] >= gameBoard.GetRows()) {
                nextMove[0] = 0;
            }
            
            if (nextMove[1] < 0) {
                nextMove[1] = gameBoard.GetColumns() - 1;
            }
            if (nextMove[1] >= gameBoard.GetColumns()) {
                nextMove[1] = 0;
            }

            content = gameBoard.getCell(nextMove[0], nextMove[1]);

        } while (content.isObstacle() || content.hasGhost());

        return nextMove;
    }
}