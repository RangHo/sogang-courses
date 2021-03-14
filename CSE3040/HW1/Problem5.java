import java.util.Scanner;

public class Problem5 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int[] scores = new int[]{ -1, -1, -1, -1, -1 };

        System.out.println("Enter exam scores of each student.");

        // Index of the best and the second best student, respectively
        int firstIndex = 0, secondIndex = 0;

        for (int i = 0; i < 5; i++) {
            System.out.printf("Score of student %d: ", i + 1);
            scores[i] = sc.nextInt();

            // If this is the best student
            if (scores[i] > scores[firstIndex]) {
                secondIndex = firstIndex;
                firstIndex = i;
            } else if (scores[i] > scores[secondIndex]) {
                secondIndex = i;
            }
        }

        System.out.printf(
            "The 1st place is student %d with %d points.\n"
            + "The 2nd place is student %d with %d points.\n",
            firstIndex + 1, scores[firstIndex],
            secondIndex + 1, scores[secondIndex]
        );

        sc.close();

        return;
    }
}

