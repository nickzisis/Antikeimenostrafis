package ce326.hw2;

import java.util.Scanner;

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
                    JSONparser.BoardMaker(filepath);
                    
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
}
