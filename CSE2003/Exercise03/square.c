#include <stdio.h>

int sqr(int);
void printOne(int);

int main(void)
{
    int num;
    printf("Input a number: ");
    scanf("%d", &num);

    printOne(sqr(num));

    return 0;
}

int sqr(int number) { return number * number; }

void printOne(int number) { printf("Result: %d\n", number); }
