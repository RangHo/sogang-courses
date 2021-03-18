#include <stdio.h>

int main(void)
{
    int a, b;

    printf("Input 2 integers: ");
    scanf("%d %d", &a, &b);

    char two = ' ';
    char three = ' ';
    char five = ' ';

    if (a % 2 == 0 && b % 2 == 0)
        two = '2';
    if (a % 3 == 0 && b % 3 == 0)
        three = '3';
    if (a % 5 == 0 && b % 5 == 0)
        five = '5';

    printf("Common divisors: %c %c %c", two, three, five);
}
