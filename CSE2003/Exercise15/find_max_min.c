#include <stdio.h>

void swap(int*, int*);
int max(int*, int);
int min(int*, int);

int main(void)
{
    int inputs[10];

    printf("Input 10 numbers below.\n");
    for (int i = 0; i < 10; i++)
        scanf("%d", &inputs[i]);

    for (int i = 0; i < 5; i++)
        swap(&inputs[i], &inputs[10 - i - 1]);

    printf("Reversed input: ");

    for (int i = 0; i < 10; i++)
        printf("%d ", inputs[i]);

    printf("\n");

    printf("Max: %d, Min: %d\n", max(inputs, 10), min(inputs, 10));

    return 0;
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int max(int* array, int size)
{
    int largest = array[0];

    for (int i = 1; i < size; i++)
        if (array[i] > largest)
            largest = array[i];

    return largest;
}

int min(int* array, int size)
{
    int smallest = array[0];

    for (int i = 1; i < size; i++)
        if (array[i] < smallest)
            smallest = array[i];

    return smallest;
}
