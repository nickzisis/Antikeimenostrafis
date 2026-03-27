package ce326.hw2;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import org.json.JSONArray;
import org.json.JSONObject;

public class JSONparser {
    public static void ErrorChecker(String filename) {
        try {
            String fileContent;

            fileContent = new String(Files.readAllBytes(Paths.get(filename)));

            JSONObject jsoncontent = new JSONObject(fileContent);
            
            int rows = jsoncontent.getInt("rows");
            int columns = jsoncontent.getInt("columns");
            int init_energy = jsoncontent.getInt("init_energy");

            JSONArray canvas = jsoncontent.getJSONArray("canvas");

            if((rows <= 0) || (columns <= 0) || (init_energy <= 0) || (canvas.length() != (rows * columns))) {
                System.out.println("Invalid information in file '" + filename + "'");
            }

            /*for (int i = 0; i < rows; i++) {
                for(int j = 0; j<columns; j++) {
                    System.out.print(canvas.get(i+j));
                    System.out.print(" ");
                }
                System.out.print("\n");
            }*/
        }
        catch (IOException e) {
            System.out.println("Unable to read '" + filename + "'");
        }

    }

    public static Board BoardMaker(String filename) {
        try {
            String fileContent;

            fileContent = new String(Files.readAllBytes(Paths.get(filename)));
            JSONObject jsoncontent = new JSONObject(fileContent);

            int rows = jsoncontent.getInt("rows");
            int columns = jsoncontent.getInt("columns");
            int init_energy = jsoncontent.getInt("init_energy");
            JSONArray canvas = jsoncontent.getJSONArray("canvas");
            
            Board GameBoard = new Board(rows, columns);
            GameBoard.SetEnergy(init_energy);

            for (int i = 0;  i < canvas.length() ; i++) {
                int row = i / columns;
                int column = i % columns;
                String symbol = canvas.getString(i);

                Position curPosition = GameBoard.getCell(row, column);
                if (symbol.equals("#")) {
                    curPosition.setObstacle(true);
                } 
                else if (symbol.equals("X")) {
                    curPosition.addContent(new Actor(row, column, init_energy));
                }
                else if (symbol.charAt(0) == '@') {
                    curPosition.addContent(new Ghost(row, column, symbol));
                }
                else if (symbol.equals("$")) {
                    curPosition.addContent(new Food(row, column, symbol , symbol.charAt(1)));
                }
                else if (symbol.equals("?")) {
                    curPosition.addContent(new MagicShield(row, column, symbol, symbol.charAt(1)));
                }
            }
            GameBoard.PrintBoard();
            return GameBoard;
        }
        catch(IOException e) {
        }
        return null;
    }    
}

