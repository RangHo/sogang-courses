#include <stdio.h>

int compare(int* a, int* b);
int main()
{

    int x, y;
    printf("Enter x, y: ");
    scanf("%d %d", &x, &y);

    if (compare(&x, &y) == 1) {
        printf("\nThe two numbers are equal.");
    }

    else {
        printf("\nThe two numbers are Not equal.");
    }

    return 0;
}

int compare(int* a, int* b)
{
    if (*a == *b) {
        return 1;
    } else {
        return 0;
    }
}
