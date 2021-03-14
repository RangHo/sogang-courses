public class Problem09 {
    public static void main(String[] args) {
        Point p1 = new Point(new double[] {
            1.0,
            2.0,
            3.0
        });
        Point p2 = new Point(new double[] {
            4.0,
            5.0,
            6.0
        });
        System.out.println("Euclidean Distance: " + EuclideanDistance.getDist(p1, p2));
        System.out.println("Manhattan Distance: " + ManhattanDistance.getDist(p1, p2));
        Point p3 = new Point(new double[] {
            1.0,
            2.0,
            3.0
        });
        Point p4 = new Point(new double[] {
            4.0,
            5.0
        });
        System.out.println("Euclidean Distance: " + EuclideanDistance.getDist(p3, p4));
        System.out.println("Manhattan Distance: " + ManhattanDistance.getDist(p3, p4));
    }
}

class Point {
    
    private int dimension;

    private double[] coordinates;

    public Point(double[] inputs) {
        this.coordinates = inputs;
        this.dimension = inputs.length;
    }

    public int getDimension() {
        return this.dimension;
    }

    public double[] getCoordinates() {
        return this.coordinates;
    }
}

class EuclideanDistance {
    public static double getDist(Point p1, Point p2) {
        if (p1.getDimension() != p2.getDimension())
            return -1.0;

        double squaredDiff = 0.0;
        for (int i = 0; i < p1.getDimension(); i++)
            squaredDiff
                += (p1.getCoordinates()[i] - p2.getCoordinates()[i])
                 * (p1.getCoordinates()[i] - p2.getCoordinates()[i]);

        return Math.sqrt(squaredDiff);
    }
}

class ManhattanDistance {
    public static double getDist(Point p1, Point p2) {
        if (p1.getDimension() != p2.getDimension())
            return -1.0;

        double absDiff = 0.0;
        for (int i = 0; i < p1.getDimension(); i++)
            absDiff += Math.abs(p1.getCoordinates()[i] - p2.getCoordinates()[i]);

        return absDiff;
    }
}

