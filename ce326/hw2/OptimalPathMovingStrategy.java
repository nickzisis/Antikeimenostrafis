package ce326.hw2;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Random;

public class OptimalPathMovingStrategy implements GhostMovingStrategy {
    @Override
    public int[] nextMove(Board gameBoard, boolean ChasedByActor, int startRow, int startColumn) {
        int r = gameBoard.GetRows();
        int c = gameBoard.GetColumns();
        int endRow = 0;
        int endColumn = 0;
        int [][] grid = new int[r][c];
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                Position content = gameBoard.getCell(i, j);
                grid[i][j] = (content.isObstacle() || content.hasGhost()) ? -1 : 1;
                if (content.getAllContents().size() > 0) {
                    for (BoardElement element : content.getAllContents()) {
                        if (element instanceof Actor) {
                            grid[i][j] = 2; // Mark the position of the Actor
                            endRow = i;
                            endColumn = j;
                            break;
                        }
                    }
                }
            }
        }

        int []x = {0,0,1,-1};//This represent 4 directions right, left, down , up
        int []y = {1,-1,0,0};
        LinkedList<int[]> q = new LinkedList<>();
        q.add(new int[]{endRow, endColumn});
    
        int[][]dist = new int[r][c];
        for(int []a : dist){
            Arrays.fill(a,-1);
        }
        dist[endRow][endColumn] = 0;
        while(!q.isEmpty()){
            int[] p = q.removeFirst();
            for(int i = 0; i < 4; i++){
                int a = p[0] + x[i];
                int b = p[1] + y[i];
                if (a == r) { a = 0; }
                if (a == -1) { a = r - 1; }
                if (b == c) { b = 0; }
                if (b == -1) { b = c - 1; }

                if(dist[a][b] == -1 && grid[a][b] != -1 ){
                    dist[a][b] = 1 + dist[p[0]][p[1]];
                    q.add(new int[]{a, b});
                }
            }
        }

        ArrayList<int[]> possibleMoves = new ArrayList<>();
        possibleMoves.add(new int[]{startRow, startColumn});    
        for(int i = 0; i < 4; i++){
            int a = startRow + x[i];
            int b = startColumn + y[i];
            if (a == r) { a = 0; }
            if (a == -1) { a = r - 1; }
            if (b == c) { b = 0; }
            if (b == -1) { b = c - 1; }

            if(grid[a][b] != -1){
                possibleMoves.add(new int[]{a, b});
            }
        }

        ArrayList<int[]> bestMoves = new ArrayList<>();
        if (ChasedByActor) {
            int maxDist = -1;
            for (int[] move : possibleMoves) {
                int currDist = dist[move[0]][move[1]];
                if (currDist != -1) {
                    if (currDist > maxDist) {
                        maxDist = currDist;
                        bestMoves.clear();
                        bestMoves.add(move);
                    }else if (currDist == maxDist) {
                        bestMoves.add(move);
                    }
                }
            }
        } else {
            int minDist = Integer.MAX_VALUE;
            for (int[] move : possibleMoves) {
                int currDist = dist[move[0]][move[1]];
                if (currDist != -1) {  
                    if (currDist < minDist) {
                        minDist = currDist;
                        bestMoves.clear();
                        bestMoves.add(move);
                    } else if (currDist == minDist) {
                        bestMoves.add(move);
                    }
                }
            }
        }
        
        if (bestMoves.isEmpty()) {
            // Αν ο Actor δεν είναι προσβάσιμος με τίποτα, το φάντασμα απλά μένει στη θέση του.
            return new int[]{startRow, startColumn};        
        }

        return bestMoves.get(new Random().nextInt(bestMoves.size()));
    }
}