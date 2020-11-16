public class Problem11 {
    public static void main(String[] args) {
        PalindromeChecker.check("abcde");
        PalindromeChecker.check("abcba");
        PalindromeChecker.check(1234);
        PalindromeChecker.check(12321);
    }
}

class PalindromeChecker {
    public static void check(int target) {
        check(Integer.toString(target));
    }

    public static void check(String target) {
        boolean isPalindrome = true;
        for (int i = 0; i < target.length(); i++)
            if (target.charAt(i) != target.charAt(target.length() - i - 1))
                isPalindrome = false;

        if (isPalindrome)
            System.out.println(target + " is a palindrome.");
        else
            System.out.println(target + " is not a palindrome.");
    }
}
