import java.io.*;
import java.util.*;

public class Problem18 {
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
        Map<String, Double> data = new HashMap<>() {
            @Override
            public String toString() {
                StringBuilder sb = new StringBuilder();

                List<Map.Entry<String, Double>> entries = new ArrayList<>(entrySet());
                entries.sort((here, there) -> {
                    if (here.getValue().equals(there.getValue()))
                        return here.getKey().compareTo(there.getKey());
                    else
                        return here.getValue().compareTo(there.getValue());
                });
                for (Map.Entry<String, Double> entry : entries)
                    sb.append(entry.getKey() + " " + entry.getValue() + "\n");
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

