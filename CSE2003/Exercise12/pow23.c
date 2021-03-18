#include <stdio.h>

void Swap(int*, int*);
int SumMultiples(int, int);

int main(void)
{
    int first, second;

    printf("Input first number: ");
    scanf("%d", &first);

    printf("Input second number: ");
    scanf("%d", &second);

    if (first < 1 || second < 1) {
        printf("Input is less than 1!\n");
        return 1;
    }

    if (first > second)
        Swap(&first, &second);

    printf("Result: %d\n", SumMultiples(first, second));

    return 0;
}

void Swap(int* num1, int* num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

int SumMultiples(int lower, int upper)
{
    int sum = 0;
    for (int i = lower; i <= upper; i++)
        if (i % 2 == 0 || i % 3 == 0)
            sum += i;

    return sum;
}
