#include <stdio.h>

int main(void)
{
    int input;
    printf("Input: ");
    scanf("%d", &input);

    (input % 2 == 0) ? printf("%d is even number.\n", input) : printf("%d is odd number.\n", input);

    return 0;
}
