import java.io.*;
import java.util.*;

public class Problem16 {
   public static void main(String args[]) {
       ArrayList<Element> list = ElementReader.readElements("input.txt");
       if(list == null) {
           System.out.println("Input file not found.");
           return;
       }
       Collections.sort(list);
       Iterator<Element> it = list.iterator();
       while(it.hasNext())
           System.out.println(it.next());
   }
}

class ElementReader {
    public static ArrayList<Element> readElements(String filename) {
        ArrayList<Element> list = new ArrayList<>();

        try {
            Scanner sc = new Scanner(new File(filename));
            while (sc.hasNext()) {
                Element item = new Element(sc.next(), sc.nextDouble());
                list.add(item);
            }

            sc.close();
        } catch (Exception e) {
            return null;
        }

        return list;
    }
}

class Element implements Comparable<Element> {
    
    private String name;

    private double price;

    public Element(String name, double price) {
        this.name = name;
        this.price = price;
    }

    @Override
    public int compareTo(Element that) {
        if (this.price == that.price)
            return this.name.compareTo(that.name);
        else
            return (int)(this.price - that.price);
    }

    @Override
    public String toString() {
        return this.name + " " + this.price;
    }
}

