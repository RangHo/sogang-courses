import java.util.Scanner;

public class Problem4 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String text = null;
        String query = "";

        System.out.print("Enter a text: ");
        text = sc.nextLine();

        while (true) {
            System.out.print("Enter a string: ");
            query = sc.nextLine();
            
            if (query.isEmpty())
                System.out.println("You must enter a string.");
            else
                break;
        }

        int occurance = 0, lastIndex = 0;
        while (text.indexOf(query, lastIndex) >= 0) {
            occurance++;
            lastIndex = text.indexOf(query, lastIndex) + query.length();
        }

        System.out.printf(
            "There are %d instances of \"%s\".\n",
            occurance, query
        );

        sc.close();
        
    }
}

