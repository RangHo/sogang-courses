import java.util.*;

public class Problem12 {
    public static void main(String[] args) {
        SubsequenceChecker.check("supercalifragilisticexpialidocious", "pads");
        SubsequenceChecker.check("supercalifragilisticexpialidocious", "padsx");
    }
}

class SubsequenceChecker {
    static void check(String str1, String str2) {
        List<Integer> matches = new ArrayList<>();
        int subsequenceIndex = 0;

        for (int i = 0; i < str1.length(); i++) {
            if (subsequenceIndex <= str2.length() &&
                str1.charAt(i) == str2.charAt(subsequenceIndex)) {
                matches.add(i);
                subsequenceIndex++;
            }
        }

        if (subsequenceIndex == str2.length()) {
            System.out.println(str2 + " is a subsequence of " + str1);
            for (Integer item : matches)
                System.out.printf("%d ", item);
            System.out.println();
        } else {
            System.out.println(str2 + " is not a subsequence of " + str1);
        }
    }
}
