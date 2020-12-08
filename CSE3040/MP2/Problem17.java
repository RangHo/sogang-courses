import java.io.*;
import java.util.*;

public class Problem17 {
    public static void main(String args[]) {
        Map<String, Double> map = MapManager.readData("input.txt");
        if (map == null) {
            System.out.println("Input file not found.");
            return;
        }
        System.out.println(map);
    }
}

class MapManager {
    public static Map<String, Double> readData(String filename) {
        Map<String, Double> data = new HashMap<String, Double>() {
            @Override
            public String toString() {
                StringBuilder sb = new StringBuilder();

                List<String> keys = new ArrayList<String>(keySet());
                keys.sort(null);
                for (String key : keys)
                    sb.append(key + " " + get(key) + "\n");
                sb.deleteCharAt(sb.length() - 1);

                return sb.toString();
            }
        };

        try {
            Scanner sc = new Scanner(new File(filename));
            while (sc.hasNext())
                data.put(sc.next(), sc.nextDouble());
            sc.close();
        } catch (Exception e) {
            return null;
        }

        return data;
    }
}

