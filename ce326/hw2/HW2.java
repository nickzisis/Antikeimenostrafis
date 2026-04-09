package ce326.hw2;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.Scanner;

public class HW2 {
    public static void main(String[] args) {
        String userInput;
        Scanner scanner = new Scanner(System.in);
        Deque<GameState> gameHistory = new ArrayDeque<>();
        Board gameBoard = null;
        printInitialMenu();
        boolean firstIteration = true;
        do { 
            userInput = scanner.nextLine();
            if (userInput.length() > 1) {
                System.out.println("Invalid option\n");
                printInitialMenu();
                continue;
            }
            if(userInput.trim().equalsIgnoreCase("q")) {
                break;
            }
            
            switch (userInput.toLowerCase()) {
                case "c":
                    if (firstIteration || gameBoard == null) {
                        System.out.println("Invalid option\n");
                        break;
                    }
                    // continue the game with the current board
                    gameBoard = gameLoop(gameBoard, gameHistory);
                    break;
                case "l":
                    firstIteration = false;
                    System.out.println("Enter input filename: ");
                    Scanner filepathScanner = new Scanner(System.in);
                    String filepath;
                    
                    filepath = filepathScanner.nextLine();
                    JSONparser.ErrorChecker(filepath);
                    gameBoard = JSONparser.BoardMaker(filepath);
                    gameBoard.setCellsRemaining(gameBoard);
                    gameHistory.clear();
                    gameBoard = gameLoop(gameBoard, gameHistory);
                    break;
                default:
                    System.out.println("Invalid option\n");
                    break;
            }
            if (firstIteration) {
                printInitialMenu();
                continue;
            }

            if((gameBoard != null) && (gameBoard.getCellsRemaining() == 0)) {
                printInitialMenu();
            }
            else {
                printMenu();
            }

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

    private static Board gameLoop(Board gameBoard, Deque<GameState> gameHistory) {
        int i = 0;
        boolean gameOver = false, enableDebug = false, legalMove = false, ChasedByActor = false;
        String userInput;
        ArrayList<Ghost> ghosts = gameBoard.getGhosts();
        Actor actor = gameBoard.getActor();
        int[] ghostDist = new int[ghosts.size()];

        System.out.println("Energy: " + gameBoard.getActorCurrentEnergy() + " Shield: " + gameBoard.getActorCurrentShield());
        gameBoard.PrintBoard();
        userInput = userInputString(gameBoard);

        while (!gameOver) {    

            switch (userInput.length()) {
                case 1 -> {
                    switch (userInput.toLowerCase()) {
                        case "y" -> {
                            if (actor.getShield() <= 0) {
                                System.out.println("No shield available. Cannot activate debug mode.");
                            } else {
                                enableDebug = !enableDebug;
                                System.err.println("Debug mode: " + (enableDebug ? "ON" : "OFF"));
                            }
                            gameBoard.PrintBoard();
                            userInput = userInputString(gameBoard);

                            continue;
                        }
                        case "x" -> { return gameBoard; }
                        case "z" -> { 
                            if (gameHistory.isEmpty()) {
                                System.out.println("No moves to undo.");
                                userInput = userInputString(gameBoard);
                                continue;
                            }
                            GameState lastState = gameHistory.pop();
                            gameBoard = lastState.getGameBoard();
                            actor = gameBoard.getActor();
                            System.out.println("Energy: " + lastState.getEnergy() + " Shield: " + lastState.getShield());
                            gameBoard.PrintBoard();
                            userInput = userInputString(gameBoard);
                            continue;
                        } // Undo
                        default -> {
                            System.out.println("Invalid input. Try again...");
                            userInput = userInputString(gameBoard);
                            continue;
                        }
                    }
                }
                case 2 -> {

                    if (Character.isDigit(userInput.charAt(0)) || Character.isLetter(userInput.charAt(1))) {
                        System.out.println("Invalid input format. Must be Letter+Number (e.g. A2). Try again...");
                        userInput = userInputString(gameBoard);
                        continue;
                    }

                    gameHistory.push(new GameState(gameBoard.copyBoard(), actor.getEnergy(), actor.getShield()));

                    legalMove = gameBoard.moveActor(userInput);
                    if (!legalMove) {
                        System.out.println("Invalid move. Try again...");
                        gameHistory.pop();
                        userInput = userInputString(gameBoard);
                        continue;
                    }
                    /* ########## GHOST MOVE ##########*/
                    // find the dinstance of each ghost from the actor
                    /* ########## GHOST MOVE ##########*/
                    if (actor.getShield() > 0) {
                        ChasedByActor = true;
                    } else {
                        ChasedByActor = false;
                        enableDebug = false;
                    }
                    if (enableDebug) {
                        gameBoard.printDebugInfo();
                    }
                    ghosts = gameBoard.getGhosts(); 
                    ghostDist = new int[ghosts.size()];
                    i = 0;
                    for (Ghost ghost : ghosts) {
                        ghostDist[i] = Math.abs(actor.getRow() - ghost.getRow()) + Math.abs(actor.getColumn() - ghost.getColumn());
                        i++;
                    }
                    // sort the ghosts by distance
                    for (i = 0; i < ghosts.size() - 1; i++) {
                        for (int j = 0; j < ghosts.size() - 1 - i; j++) {
                            if (ghostDist[j] > ghostDist[j + 1]) {
                                int tempDist = ghostDist[j];
                                ghostDist[j] = ghostDist[j + 1];
                                ghostDist[j + 1] = tempDist;

                                Ghost tempGhost = ghosts.get(j);
                                ghosts.set(j, ghosts.get(j + 1));
                                ghosts.set(j + 1, tempGhost);
                            }else if (ghostDist[j] == ghostDist[j + 1]) {
                                // if two ghosts are at the same distance, sort them by row
                                if (ghosts.get(j).getRow() > ghosts.get(j + 1).getRow()) {
                                    Ghost tempGhost = ghosts.get(j);
                                    ghosts.set(j, ghosts.get(j + 1));
                                    ghosts.set(j + 1, tempGhost);
                                } else if (ghosts.get(j).getRow() == ghosts.get(j + 1).getRow()){
                                    if (ghosts.get(j).getColumn() > ghosts.get(j + 1).getColumn()) {
                                        Ghost tempGhost = ghosts.get(j);
                                        ghosts.set(j, ghosts.get(j + 1));
                                        ghosts.set(j + 1, tempGhost);
                                    }
                                }
                            }
                        }
                    }
                    for (Ghost ghost : ghosts) {
                        int[] nextMove = ghost.NextMove(gameBoard, ChasedByActor);
                        if (enableDebug) {
                            if (ghost.getSymbol().charAt(1) == 'y') {
                                System.err.println("Ghost [RandomMovingStrategy] OLD Position [" + gameBoard.rowMatcher(ghost.getRow()) + (ghost.getColumn() + 1) + "], NEW Position [" + gameBoard.rowMatcher(nextMove[0]) + (nextMove[1] + 1) + "]");
                            } else {
                                System.err.println("Ghost [OptimalMovingStrategy] OLD Position [" + gameBoard.rowMatcher(ghost.getRow()) + (ghost.getColumn() + 1) + "], NEW Position [" + gameBoard.rowMatcher(nextMove[0]) + (nextMove[1] + 1) + "]");
                            }
                        }
                        if (nextMove[0] == actor.getRow() && nextMove[1] == actor.getColumn()) {
                            if (actor.getShield() > 0) {
                                Position ghostPosition = gameBoard.getCell(ghost.getRow(), ghost.getColumn());
                                ghostPosition.removeContent(ghost);
                                continue;
                            } else {
                                gameBoard.moveGhost(ghost, nextMove[0], nextMove[1]);
                                gameBoard.PrintBoard();
                                System.out.println("You lost because of a ghost killing you! Try again!\n");
                                gameOver = true;
                                break;     
                            }
                        }
                        gameBoard.moveGhost(ghost, nextMove[0], nextMove[1]);
                    }   
                    if (gameOver) {
                        break;
                    }

                    if (gameBoard.getCellsRemaining() == 0) {
                        System.out.println("YOU WON! Congratulations!");
                        gameOver = true;
                        break;
                    }

                    System.out.println("Energy: " + gameBoard.getActorCurrentEnergy() + " Shield: " + gameBoard.getActorCurrentShield());
                    gameBoard.PrintBoard();
                    userInput = userInputString(gameBoard);
                }
                default -> {
                    System.out.println("Invalid input. Try again...");
                    userInput = userInputString(gameBoard);
                    continue;
                }
            }

            if (gameBoard.getActorCurrentEnergy() <= 0) {
                gameBoard.PrintBoard();
                System.out.println("You lost because of no energy! Try again!");
                gameOver = true;
                break;
            }

        }
        return gameBoard;
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