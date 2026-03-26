package ce326.hw2;

public interface GhostMovingStrategy {
    int[] NextMove(Board gameBoard, boolean ChasedByActor, int startRow, int startColumn);
}
