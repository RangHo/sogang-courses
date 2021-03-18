#include <stdio.h>

int add(int, int);

int main(void)
{
    int a, b;
    int result;

    printf("Input a number: ");
    scanf("%d", &a);
    printf("Input another number: ");
    scanf("%d", &b);

    result = add(a, b);

    printf("%d + %d = %d\n", a, b, result);

    return 0;
}

int add(int left, int right) { return left + right; }
