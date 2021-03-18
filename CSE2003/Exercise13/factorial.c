#include <stdio.h>

int Factorial(int);

int main(void)
{
    int n;

    printf("Input n: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Input must be a whole number!\n");
        return -1;
    }

    printf("%d! = %d\n", n, Factorial(n));

    return 0;
}

int Factorial(int n)
{
    int index = 0;
    int current = 1;

    if (n == 0)
        return 1;

    if (n == 1)
        return 1;

    do {
        index++;
        current *= index;
    } while (index < n);

    return current;
}
