package ce326.hw2;

import java.util.Scanner;
import org.json.JSONArray;
import org.json.JSONObject;

public class HW2 {
    public static void main(String[] args) {
        String userInput;
        Scanner scanner = new Scanner(System.in);
        printInitialMenu();
        do { 
           
            userInput = scanner.nextLine();
            if (userInput.length() > 1) {
                System.out.println("Invalid option\n");
                continue;
            }
            
            if(userInput.trim().equalsIgnoreCase("q")) {
                break;
            }
            
            switch (userInput.toLowerCase()) {
                case "c":
                    //continues game
                    break;
                case "l":
                    System.out.println("Enter input filename: ");
                    Scanner filepathScanner = new Scanner(System.in);
                    String filepath;
                    
                    filepath = filepathScanner.nextLine();
                    JSONparser.ErrorChecker(filepath);
                    Board gameBoard = JSONparser.BoardMaker(filepath);
                    gameLoop(gameBoard);
                    break;
                default:
                    System.out.println("Invalid option\n");
                    break;
            }
            
            printMenu();
        } while (true);
        
        scanner.close();
    }

    private static void printInitialMenu() {
        System.out.println("- Load New Game  (L/l)");
        System.out.println("- Quit           (Q/q)\n");
        System.out.println("Your option: ");
    }

    private static void printMenu() {
        System.out.println("- Load New Game  (L/l)");
        System.out.println("- Continue game  (C/c)");
        System.out.println("- Quit           (Q/q)\n");
        System.out.println("Your option: ");
    }

    private static void gameLoop(Board gameBoard) {
        int rows = gameBoard.GetRows();
        int columns = gameBoard.GetColumns();
        int energy = gameBoard.GetEnergy();
        int shield = gameBoard.GetShield();
        int moves = 0;
        JSONArray moveHistory = new JSONArray();

        JSONObject currState = new JSONObject();
        currState.put("move", moves);
        currState.put("energy", energy);
        currState.put("shield", shield);
        currState.put("canvas", gameBoard);

        moveHistory.put(currState);

        
        
    }
}
