#include <stdio.h>

int Fibonacci(int);

int main(void)
{
    int n;

    printf("Input n: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Input must be a whole number!\n");
        return -1;
    }

    printf("fib(%d) = %d\n", n, Fibonacci(n));

    return 0;
}

int Fibonacci(int n)
{
    int n2 = 0; // n - 2
    int n1 = 1; // n - 1
    int index = 1;
    int current = 0;

    if (n == 0)
        return n2;

    if (n == 1)
        return n1;

    do {
        current = n2 + n1;
        index++;

        n2 = n1;
        n1 = current;
    } while (index < n);

    return current;
}
