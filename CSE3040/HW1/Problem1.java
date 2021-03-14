import java.util.Scanner;

public class Problem1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("ASCII code teller. Enter a letter: ");
        
        String buffer = sc.nextLine();

        // Check if the input is an alphabet letter
        if (buffer.matches("^[a-zA-Z]$")) {
            char letter = buffer.charAt(0);
            System.out.println(
                "The ASCII code of " + letter + " is " + (int)letter + "."
            );
        } else {
            System.out.println(
                "You must input a single uppercase or lowercase alphabet."
            );
        }

        sc.close();

        return;
    }
}

