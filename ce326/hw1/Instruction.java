package ce326.hw1;

import java.util.ArrayDeque;
import java.util.Deque;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Stack;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Instruction {
    String instr;
    
    public Instruction(String splittedInput) {
      this.instr = splittedInput;
    }

    public LinkedList<String> tokenMaker(){

        String regex = "-?[0-9]+(\\.[0-9]+)?|[a-zA-Z]+|[+\\-*/^=()]";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(this.instr);
        LinkedList<String> tokenList = new LinkedList<>();

        while (matcher.find()) {
            tokenList.add(matcher.group());
        }   
        
        return tokenList;
    }

    public void errorChecker (LinkedList<String> tokenList) throws ParserException{
        int leftParenthesis = 0;
        int rightParenthesis = 0;
        int equal = 0;
        String token1, token2;
        int size  = tokenList.size();
        String operators = "+-*/^=;"; //We didnt check for -.
        String parentheses = "()"; //We didnt check for parentheses.

        for (int i = 0; i < size - 1; i++){
            token1 = tokenList.get(i);
            token2 = tokenList.get(i+1);
            
            if ((token1.equals("(")) || ((i == size - 1) && (token2.equals("(")))){
                leftParenthesis++;
            }
            if ((token2.equals(")")) || ((i == 0) && (token1.equals(")")))){
                rightParenthesis++;
            }
            if (token1.equals("=") || ((i == size - 1) && (token2.equals("=")))){
                equal++;
            }
            
            if ((Character.isDigit(token1.charAt(0))) && ((token2.length() > 1) && (token2.contains("-"))) || ((token1.contains("-")) && ((token2.length() > 1) && (token2.contains("-"))))){
                tokenList.add(i+1, token2.substring(1));
                tokenList.add(i+1, "-");
                tokenList.remove(i+3);
                size++;
                token2 = tokenList.get(i+1);
            }

            if (equal > 1){
                throw new ParserException("Multiple assignment operator in expression");
            }
            if (((operators.contains(token1)) && (operators.contains(token2)) && !(token1.equals("="))) || ((i == size - 2) && (operators.contains(token2)))){
                throw new ParserException("Expecting operand between operators");
            }
            
            //Checking for parentheses aswell.
            if (!(operators.contains(token1)) && !(operators.contains(token2)) && !((token1.equals("-")) || (token2.equals("-")) || (parentheses.contains(token1)) || (parentheses.contains(token2)))){
                throw new ParserException("Expecting operator between operands");
            }
        }

        if (leftParenthesis > rightParenthesis){
            throw new ParserException("Expecting ) at end of expression");
        }
        else if (rightParenthesis > leftParenthesis){
            throw new ParserException("Expecting ( before closing");
        }
    }

    //Makes the Shunting Yard algorithm and returns the output queue
    //for later use in the RPN.
    public Deque<String> ShuntingYard(LinkedList<String> tokenList){
        Deque<String> result = new ArrayDeque<>();
        Stack<String> operatorStack = new Stack<>();
        String operators = "+-*/^";

        for (int i=0; i < tokenList.size() ; i++) {
            //If =, then skip.
            if (tokenList.get(i).equals("=")) {
                continue;
            }
            
            //If letter or number
            if (!operators.contains(tokenList.get(i)) && (!tokenList.get(i).equals("(")) && (!tokenList.get(i).equals(")"))) {
                result.addLast(tokenList.get(i));
            }
            //If left parenthesis
            else if (tokenList.get(i).equals("(")) {
                operatorStack.push(tokenList.get(i));
            }
            //If right parenthesis
            else if (tokenList.get(i).equals(")")) {
                while ((!operatorStack.isEmpty()) && (!operatorStack.peek().equals("("))) {
                    result.addLast(operatorStack.pop());
                }
                
                //Removes left parenthesis
                if ((!operatorStack.isEmpty()) && (operatorStack.peek().equals("("))) {
                    operatorStack.pop();
                }
            }
            //If operator
            else if (operators.contains(tokenList.get(i))) {

                while ((!(operatorStack.empty())) && (getPriority(operatorStack.peek()) >= getPriority(tokenList.get(i)))) {
                    result.addLast(operatorStack.pop());
                }

                operatorStack.push(tokenList.get(i));
            }
        }

        /*  Stack Print
        if (!operatorStack.empty()) {
            System.out.println("The Stack contains: ");
            for (int i=0; i < operatorStack.size() ; i++) {
                System.out.println(operatorStack.get(i) + " ");
            }
            System.out.println("Top of the stack is: " + operatorStack.peek() + "\n");
        }*/

        /*  Queue Print
        if(!result.isEmpty()) {
            System.out.println("The Queue contains: ");
            System.out.println(result + " ");
        }*/

        //Adds the leftover operands after the instruction is over
        while (!operatorStack.isEmpty()) {
            result.addLast(operatorStack.pop());
        }

        return result;
    }

    //Gets the priority for every operator.
    private int getPriority(String operator) {
        switch (operator) {
            case "+":
            case "-":
                return 1;
            case "*":
            case "/":
                return 2;
            case "^":
                return 3;
            default:
                return -1;
        }
    }

    //Calculates the RPN given g=the SYResult, and checks the hashmap for if the variables are in there.
    public double RPNcalculator(Deque<String> SYResult, HashMap<String, Double> variables) throws ParserException{
        Stack<Double> resultStack = new Stack<>();
        String operatorString = "+-*/^";
        char operator; //This is used for the later operation.
        String currentToken; //The current token from the SYResult.
        double num1, num2, res;

        //For as long as it isn't empty.
        while (!SYResult.isEmpty()) {
            currentToken = SYResult.poll();

            //If it's not an operator then checks if it's a digit, if it is then push it to the stack,
            //if not then checks if it is a variable. If it exists as a variable return its value and
            //push it to the stack.
            if (!(operatorString.contains(currentToken)) || ((currentToken.contains("-")) && (currentToken.length() > 1))) {

                if (Character.isDigit(currentToken.charAt(0))) {
                    resultStack.push(Double.valueOf(currentToken));
                }
                else if ((currentToken.contains("-")) && (Character.isDigit(currentToken.charAt(1)))) {
                    resultStack.push(Double.valueOf(currentToken));
                } 
                else {
                    if(!variables.containsKey(currentToken)) {
                        throw new ParserException("Unknown variable " + currentToken);
                    }
                    resultStack.push(variables.get(currentToken));
                }
            }
            
            //If its an operator then do the operation and push the result.
            else {
                
                num1 = resultStack.pop();
                num2 = resultStack.pop();
                operator = currentToken.charAt(0);
                
                res = GetResult(num1, num2, operator);
                
                resultStack.push(res);
            }
        }

        res = resultStack.pop();
        return res;
   }

   private double GetResult(double num1, double num2, char operator) {
        double result = 0;
    
        switch (operator) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num2 - num1;
                break;
            case '*':
                result = num2 * num1;
                break;
            case '/':
                result = num2 / num1;
                break;
            case '^':
                result = Math.pow(num2, num1);
                break;
            default:
                break;
        }

        return result;
   }
}