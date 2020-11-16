import java.nio.file.*;
import java.util.*;

public class Problem13 {
    public static void main(String[] args) {
        Text t = new Text();
        if (t.readTextFromFile("input_prob13.txt")) {
            for (char c = 'a'; c <= 'z'; c++) {
                System.out.println(c + ": " + t.countChar(c));
            }
        }
    }
}

class Text {
    private String fileContent;

    public boolean readTextFromFile(String filename) {
        try {
            List<String> lines = Files.readAllLines(Paths.get(filename));
            this.fileContent = String.join(System.lineSeparator(), lines);
        } catch (Exception e) {
            System.out.println("Input file not found.");
            return false;
        }

        return true;
    }

    public int countChar(char target) {
        int count = 0;
        for (char item : this.fileContent.toCharArray())
            if (Character.toLowerCase(item) == target)
                count++;

        return count;
    }
}
