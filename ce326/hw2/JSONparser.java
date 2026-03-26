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
        }
        catch (IOException e) {
            System.out.println("Unable to read '" + filename + "'");
        }

    }

    public static void BoardMaker(String filename) {
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

            for (int i = 1; i < canvas.length() ; i++) {
                System.out.println(i + ((i / columns)) + (i % columns) + "\n");

                GameBoard.AddToBoard((i / columns), (i % columns), canvas.getString(i));
            }
            GameBoard.PrintBoard();
        }
        catch(IOException e) {
        }
    } 
}

