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
        }
        catch (IOException e) {
            System.out.println("Unable to read '" + filename + "'");
        }
     

    }
}

