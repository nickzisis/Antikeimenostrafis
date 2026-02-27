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

    public void errorChecker (LinkedList<String> tokenlist){
        if (){
            throw new ParserException("Expecting ; at the end of line");
        }
    } 
}