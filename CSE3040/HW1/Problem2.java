import java.util.Scanner;

public class Problem2 {
    private static final int ANSWER_RANGE = 100;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Draw a random number
        int answer = (int)(Math.random() * Problem2.ANSWER_RANGE + 1);
        
        boolean correct = false;
        int trial = 1;
        int lowerBound = 1, upperBound = Problem2.ANSWER_RANGE;
        while (!correct) {
            System.out.printf(
                "[%d] Guess a number (%d-%d): ",
                trial, lowerBound, upperBound
            );
            int guess = sc.nextInt();

            // Check the input range
            if (1 > guess || Problem2.ANSWER_RANGE < guess) {
                System.out.println("Not in range!");
                continue;
            }

            if (guess > answer) {
                System.out.println("Too large!");
                upperBound = guess - 1;
            } else if (guess < answer) {
                System.out.println("Too small!");
                lowerBound = guess + 1;
            } else {
                correct = true;
                break;
            }

            // Increment the trial count
            trial++;

        }

        System.out.println("Correct! Number of guesses: " + trial);

        sc.close();

        return;
    }
}

