import java.io.*;
import java.util.*;

public class Problem14 {
    public static void main(String[] args) {
        FruitBox<Fruit> box = new FruitBox<>();
        boolean rv = ItemReader.fileToBox("input_prob14.txt", box);
        if (rv == false)
            return;
        box.add(new Fruit("orange", 9.99));
        System.out.println("----------------");
        System.out.println("    Summary");
        System.out.println("----------------");
        System.out.println("number of items: " + box.getNumItems());
        System.out.println("most expensive item: " + box.getMaxItem() + " (" +
                           box.getMaxPrice() + ")");
        System.out.println("cheapest item: " + box.getMinItem() + " (" +
                           box.getMinPrice() + ")");
        System.out.printf("average price of items: %.2f", box.getAvgPrice());
    }
}

class Fruit {
    private String name;
    private double price;

    public Fruit(String name, double price) {
        this.name = name;
        this.price = price;
    }

    public String getName() {
        return this.name;
    }

    public double getPrice() {
        return this.price;
    }
}

class FruitBox<T extends Fruit> {
    private List<T> items;

    public FruitBox() {
        this.items = new ArrayList<>();
    }

    public void add(T item) {
        this.items.add(item);
        System.out.println(item.getName() + " " + item.getPrice());
    }

    public int getNumItems() {
        return this.items.size();
    }

    public String getMaxItem() {
        String maxName = null;
        double maxCost = Double.MIN_VALUE;

        for (T item : this.items) {
            if (item.getPrice() > maxCost) {
                maxName = item.getName();
                maxCost = item.getPrice();
            }
        }

        return maxName;
    }

    public double getMaxPrice() {
        double maxCost = Double.MIN_VALUE;

        for (T item : this.items) {
            if (item.getPrice() > maxCost) {
                maxCost = item.getPrice();
            }
        }

        return maxCost;
    }

    public String getMinItem() {
        String minName = null;
        double minCost = Double.MAX_VALUE;

        for (T item : this.items) {
            if (item.getPrice() < minCost) {
                minName = item.getName();
                minCost = item.getPrice();
            }
        }

        return minName;
    }

    public double getMinPrice() {
        double minCost = Double.MAX_VALUE;

        for (T item : this.items) {
            if (item.getPrice() < minCost) {
                minCost = item.getPrice();
            }
        }

        return minCost;
    }

    public double getAvgPrice() {
        double sum = 0.0;
        for (T item : this.items)
            sum += item.getPrice();

        return sum / this.items.size();
    }
}

class ItemReader {
    public static boolean fileToBox(String filename, FruitBox<Fruit> box) {
        try {
            Scanner sc = new Scanner(new File(filename));
            while (sc.hasNext()) {
                Fruit item = new Fruit(sc.next(), sc.nextDouble());
                box.add(item);
            }
            sc.close();
        } catch (Exception e) {
            System.out.println("Input file not found.");
            return false;
        }

        return true;
    }
}
