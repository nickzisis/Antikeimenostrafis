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
        int i = 0;
        int minDist = Integer.MAX_VALUE;
        boolean gameOver = false, enableDebug = false, legalMove = false, ChasedByActor = false;
        String userInput;
        ArrayList<Ghost> ghosts = gameBoard.getGhosts();
        Actor actor = gameBoard.getActor();
        int[] ghostDist = new int[ghosts.size()];

        while (!gameOver) {
            
            if(enableDebug) {
                gameBoard.printDebugInfo();
            }
            
            gameBoard.PrintBoard();
            userInput = userInputString(gameBoard);
            
            if(userInput.length() < 2) {
                switch (userInput.toLowerCase()) {
                    case "y" -> enableDebug = true;
                    case "x" -> {
                        //saves and goes back to the menu
                        return;
                    }
                    case "z" -> {
                        //undoes
                        continue;
                    }
                    default -> {
                        System.out.println("Invalid input. Try again...");
                        continue;
                    }
                }
            }
            else {
                legalMove = gameBoard.moveActor(userInput);
                if (!legalMove) {
                    System.out.println("Invalid move. Try again...");
                    continue;
                }
                /* ########## GHOST MOVE ##########*/
                // find the dinstance of each ghost from the actor
                i = 0;
                for (Ghost ghost : ghosts) {
                    ghostDist[i] = Math.abs(actor.getRow() - ghost.getRow()) + Math.abs(actor.getColumn() - ghost.getColumn());
                    i++;
                }
                // sort the ghosts by distance
                for (i = 0; i < ghosts.size(); i++) {
                    for (int j = 0; j < ghosts.size() - i; j++) {
                        if (ghostDist[j] > ghostDist[j + 1]) {
                            int tempDist = ghostDist[j];
                            ghostDist[j] = ghostDist[j + 1];
                            ghostDist[j + 1] = tempDist;

                            Ghost tempGhost = ghosts.get(j);
                            ghosts.set(j, ghosts.get(j + 1));
                            ghosts.set(j + 1, tempGhost);
                        }
                    }
                }
                for (Ghost ghost : ghosts) {
                    int[] nextMove = ghost.NextMove(gameBoard, ChasedByActor);
                    int[] ghostPos = ghost.getPosition();
                    if 
                }
            }



            //For the undo
            JSONArray moveHistory = new JSONArray();
            JSONObject currState = new JSONObject();
            currState.put("move", moves);
            currState.put("energy", energy);
            currState.put("shield", shield);
            currState.put("canvas", gameBoard);
            moveHistory.put(currState);
        }
    }

    private static String userInputString(Board gameBoard) {
        String userInput;
        int toASCII = 65;
        Scanner scanner = new Scanner(System.in);

        //Make a function for the print
        while(true) {
            System.out.print("Enter move [A-" + (char)(toASCII + gameBoard.GetRows() - 1) + "]: ");
            System.out.print("[1- " + (gameBoard.GetColumns()) + "] ");
            System.out.print("or command (Z/X/Y for undo/exit/debug): \n");
            
            userInput = scanner.nextLine().trim();
            if(userInput.length() > 2) {
                System.out.println("Invalid input. Try again...");
            }
            else if ((userInput.length() == 2) && (Character.isDigit(userInput.charAt(0)))) {
                System.out.println("Invalid input. Try again...");
            }
            else if ((userInput.length() == 2) && (Character.isLetter(userInput.charAt(1)))) {
                System.out.println("Invalid input. Try again...");
            }
            else if ((!userInput.equalsIgnoreCase("x")) || 
                        (!userInput.equalsIgnoreCase("y")) || 
                        (!userInput.equalsIgnoreCase("z"))) {
                        System.out.println("Invalid input. Try again...");
            }
            else {
                break;
            }
        }
        return userInput;
    }
}