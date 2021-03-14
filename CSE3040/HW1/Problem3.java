import java.util.Scanner;

public class Problem3 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String text = null;
        char letter = '\0';

        System.out.print("Enter a text: ");
        text = sc.nextLine();

        while (letter == '\0') {
            System.out.print("Enter a letter: ");
            String buffer = sc.nextLine();

            if (buffer.length() != 1) {
                System.out.println("You must enter a single letter.");
                continue;
            }

            letter = buffer.charAt(0);
        }

        int occurance = 0;
        for (char textChar : text.toCharArray())
            if (textChar == letter)
                occurance++;

        System.out.printf(
            "There are %d %c's in the text.\n",
            occurance, letter
        );

        sc.close();

        return;
    }
}

