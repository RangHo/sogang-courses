import java.io.*;
import java.nio.file.*;
import java.util.*;

public class Problem15 {
    public static void main(String[] args) {
        ArrayList<Item> list = new ArrayList<>();
        boolean rv = MyFileReader.readDataFromFile("input_prob15.txt", list);
        if (rv == false) {
            System.out.println("Input file not found.");
            return;
        }
        for (Item it : list)
            System.out.println(it);
    }
}

class Item {
    private String word;
    private int occurrences;

    public Item(String word) {
        this.word = word;
        this.occurrences = 1;
    }

    public String getWord() {
        return this.word;
    }

    public void incrementOccurences() {
        this.occurrences++;
    }

    @Override
    public String toString() {
        return this.word + " " + this.occurrences;
    }
}

class MyFileReader {
    public static boolean readDataFromFile(String filename, List<Item> list) {
        try {
            Scanner sc = new Scanner(new File(filename));
            while (sc.hasNext()) {
                String word = sc.next().toLowerCase();
                boolean found = false;
                for (Item item : list) {
                    if (item.getWord().equals(word)) {
                        item.incrementOccurences();
                        found = true;
                    }
                }

                if (!found)
                    list.add(new Item(word));
            }
            sc.close();
        } catch (Exception e) {
            return false;
        }

        return true;
    }
}
