#include <stdio.h>

int x = 1;

int Fibonacci(int*);

int main(void)
{
    int x = 0;

    printf("Fibo(2) = %d\n", Fibonacci(&x));
    printf("Fibo(3) = %d\n", Fibonacci(&x));
    printf("Fibo(4) = %d\n", Fibonacci(&x));
    printf("Fibo(5) = %d\n", Fibonacci(&x));
    printf("Fibo(6) = %d\n", Fibonacci(&x));
    printf("Fibo(7) = %d\n", Fibonacci(&x));
    printf("Fibo(8) = %d\n", Fibonacci(&x));
    printf("Fibo(9) = %d\n", Fibonacci(&x));
}

int Fibonacci(int* y)
{
    x = x + *y;
    *y = x - *y;
    return x;
}
