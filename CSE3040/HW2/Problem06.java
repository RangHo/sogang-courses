public class Problem06 {

    public static void main(String[] args) {
        IntSequence seq = new FibonacciSequence();
        for (int i = 0; i < 20; i++) {
            if (!seq.hasNext())
                break;
            System.out.print(seq.next() + " ");
        }
        System.out.println(" ");
    }
}

interface IntSequence {

    boolean hasNext();

    int next();
}

class FibonacciSequence implements IntSequence {

    private boolean isInitial;

    private int current;

    private int previous;

    public FibonacciSequence() {
        this.isInitial = true;
        this.current = 0;
        this.previous = 0;
    }

    public boolean hasNext() {
        return true;
    }

    public int next() {
        if (this.isInitial) {
            if (this.current == 0) {
                this.current = 1;
                return this.previous;
            } else {
                this.isInitial = false;
                return this.current;
            }
        }

        this.current += this.previous;
        this.previous = this.current - this.previous;

        return this.current;
    }
}

