#include <stdio.h>

int main()
{
    int n, a, b, c, d;

    printf("Enter an integer.\n");
    scanf("%d", &n);

    a = n / 1000;
    b = (n / 100) % 10;
    c = (n / 10) % 10;
    d = n % 10;

    printf("Sum of all digits: %d \n", a + b + c + d);

    return 0;
}