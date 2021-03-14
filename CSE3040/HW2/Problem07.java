import java.util.*;

public class Problem07 {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        System.out.print("Enter a positive integer: ");
        String str = in.nextLine();
        int num = Integer.parseInt(str);

        in.close();

        System.out.println("Integer: " + num);
        IntSequenceStr seq = new BinarySequenceStr(num);

        System.out.print("Binary number: ");
        while (seq.hasNext())
            System.out.print(seq.next());
        System.out.println(" ");
    }
}

interface IntSequenceStr {

    boolean hasNext();

    String next();
}

class BinarySequenceStr implements IntSequenceStr {

    private String binaryString;

    private int currentIndex;

    public BinarySequenceStr(int num) {
        this.binaryString = Integer.toBinaryString(num);
    }

    public boolean hasNext() {
        return this.currentIndex < this.binaryString.length();
    }

    public String next() {
        return this.binaryString.substring(this.currentIndex, this.currentIndex++ + 1);
    }
}


