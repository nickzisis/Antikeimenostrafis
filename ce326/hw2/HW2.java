package ce326.hw2;

import java.util.Scanner;
import org.json.JSONArray;
import org.json.JSONObject;
import java.util.ArrayList;

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
        boolean gameOver = false, enableDebug = false, legalMove = false;
        String userInput;
        ArrayList<Ghost> ghosts = gameBoard.getGhosts();
        JSONArray moveHistory = new JSONArray();

        while (!gameOver) {
            
            if(enableDebug) {
                gameBoard.printDebugInfo();
            }
            
            System.out.println("Energy: " + gameBoard.getActorCurrentEnergy() + " Shield: " + gameBoard.getActorCurrentShield());
            gameBoard.PrintBoard();
            userInput = userInputString(gameBoard);
            
            if(userInput.length() == 1) {
                switch (userInput.toLowerCase()) {
                    case "y" -> {
                        enableDebug = !enableDebug;
                        System.out.println("Debug mode: " + (enableDebug ? "ON" : "OFF"));
                        continue;
                    }
                    case "x" -> { return; }
                    case "z" -> { continue; } // Undo
                    default -> {
                        System.out.println("Invalid input. Try again...");
                        continue;
                    }
                }
            }
            else if (userInput.length() >= 2) {
                if (Character.isDigit(userInput.charAt(0)) || Character.isLetter(userInput.charAt(1))) {
                    System.out.println("Invalid input format. Must be Letter+Number (e.g. A2). Try again...");
                    continue;
                }
                
                legalMove = gameBoard.moveActor(userInput);
                if (!legalMove) {
                    System.out.println("Invalid move. Try again...");
                    continue; 
                }
                
                moves++;
            }
            else {
                System.out.println("Invalid input. Try again...");
                continue;
            }

            if (gameBoard.getActorCurrentEnergy() <= 0) {
                gameBoard.PrintBoard();
                System.out.println("YOU LOST\n");
                gameOver = true;
                break;
            }

            // for the undo
            JSONObject currState = new JSONObject();
            currState.put("move", moves);
            currState.put("energy", gameBoard.getActorCurrentEnergy()); 
            currState.put("shield", gameBoard.GetShield());
            currState.put("canvas", gameBoard);
            moveHistory.put(currState);
        }
    }
    

    private static String userInputString(Board gameBoard) {
        int toASCII = 65;
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter move [A-" + (char)(toASCII + gameBoard.GetRows() - 1) + "]: ");
        System.out.print("[1- " + (gameBoard.GetColumns()) + "] ");
        System.out.print("or command (Z/X/Y for undo/exit/debug): \n");
           
        return scanner.nextLine().trim();
    }
}