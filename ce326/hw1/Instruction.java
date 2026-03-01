//package hw1;

import java.util.LinkedList;
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
            System.out.print( matcher.group() + "|");
            tokenList.add(matcher.group());
        }   
        System.out.println("\n");
        for (String str: tokenList){
            System.out.println(str + " ");
        }

        return tokenList;
    }

    public void errorChecker (LinkedList<String> tokenList) throws ParserException{
        int leftParenthesis = 0;
        int rightParenthesis = 0;
        int equal = 0;
        String token1, token2;
        int size  = tokenList.size();
        String operands = "+*/^=()";

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

            if (equal > 1){
                throw new ParserException("Multiple assignment operator in expression");
            }
            if ((operands.contains(token1)) && (operands.contains(token2)) && !(token1.equals("="))){
                throw new ParserException("Expecting operand between operators");
            }
            if (!(operands.contains(token1)) && !(operands.contains(token2)) && !((token1.equals("-")) || (token2.equals("-")))){
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

  //  public void RPNcalculator(Variables){

//    }
}