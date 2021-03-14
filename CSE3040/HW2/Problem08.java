public class Problem08 {
    public static double sumArea(Shape[] shapes) {
        double result = 0.0;

        for (Shape shape : shapes)
            result += shape.getArea();

        return result;
    }

    public static void main(String[] args) {
        Shape[] arr = {
            new Circle(5.0),
            new Square(4.0),
            new Rectangle(3.0, 4.0),
            new Square(5.0)
        };

        System.out.println("Total area of the shapes is: " + sumArea(arr));
    }
}

abstract class Shape {
    public abstract double getArea();
}

class Circle extends Shape {

    private double radius;

    public Circle(double radius) {
        this.radius = radius;
    }

    @Override
    public double getArea() {
        return Math.PI * this.radius * this.radius;
    }
}

class Square extends Shape {

    private double side;

    public Square(double side) {
        this.side = side;
    }

    @Override
    public double getArea() {
        return this.side * this.side;
    }
}

class Rectangle extends Shape {

    private double width;

    private double height;

    public Rectangle(double width, double height) {
        this.width = width;
        this.height = height;
    }

    @Override
    public double getArea() {
        return this.width * this.height;
    }
}


