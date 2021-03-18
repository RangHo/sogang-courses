#include <stdio.h>

int main(void)
{
    int a, b;
    printf("Enter 2 numbers: ");
    scanf("%d %d", &a, &b);

    int a1 = a % 10;
    a = a / 10;
    int a10 = a % 10;
    a = a / 10;
    int a100 = a % 10;
    a = a / 10;

    int b1 = b % 10;
    b = b / 10;
    int b10 = b % 10;
    b = b / 10;
    int b100 = b % 10;
    b = b / 10;

    int count = 0;

    if (a1 + b1 >= 10)
        count++;
    if (a10 + b10 >= 10)
        count++;
    if (a100 + b100 >= 10)
        count++;

    printf("%d carry operations.", count);

    return 0;
}
