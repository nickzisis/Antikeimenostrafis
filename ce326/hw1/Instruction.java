//package hw1;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Instruction {
    public String makis(String splittedInput) {
        String regex = "-?[0-9]+(\\.[0-9]+)?|[a-zA-Z]+|[+\\-*/^=()]";

        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(splittedInput);

        while (matcher.find()) {
            System.out.print( matcher.group() + "|");
        }

        return regex;
    }
}
//// nwntas