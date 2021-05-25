#include <stdio.h>

int n = 0;

int fib(int);

int main()
{
    printf("Enter n value.\n");
    scanf("%d", &n);

    printf("%d", fib(n));
    return 0;
}

int fib(int n)
{
    int sum;

    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        sum = fib(n - 1) + fib(n - 2);
    }

    return sum;
}