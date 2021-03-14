public class Problem10 {
    public static void main(String[] args) {
        Points p1 = new Points(new double[] {
            1.0, 2.0, 3.0
        });
        Points p2 = new Points(new double[] {
            4.0, 5.0, 6.0
        });
        System.out.println(p1);
        System.out.println(p2);
        System.out.println(p1.equals(p2));
        Points p3 = new Points(new double[] {
            1.0, 4.0, 7.0
        });
        Points p4 = new Points(new double[] {
            3.0, 9.0
        });
        System.out.println(p3);
        System.out.println(p4);
        System.out.println(p3.equals(p4));
        Points p5 = new Points(new double[] {
            1.0, 2.0
        });
        Points p6 = null;
        System.out.println(p5);
        System.out.println(p6);
        System.out.println(p5.equals(p6));
    }
}

class Points {
    
    private double[] coordinates;

    private double sum;

    public Points(double[] inputs) {
        this.coordinates = inputs;

        this.sum = 0.0;
        for (double point : inputs)
            this.sum += point;
    }

    @Override
    public String toString() {
        return "[sum of points: " + this.sum + "]";
    }

    @Override
    public boolean equals(Object that) {
        if (!(that instanceof Points))
            return false;

        return this.sum == ((Points)that).sum;
    }
}

