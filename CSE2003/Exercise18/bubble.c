#include <stdio.h>

#define ARRAY_LENGTH 100

void swap(int*, int*);

int main(void)
{
    FILE* input = fopen("input34.txt", "r");

    int numbers[ARRAY_LENGTH] = { 0 };

    for (int i = 0; i < ARRAY_LENGTH && !feof(input); i++)
        fscanf(input, "%d\n", &numbers[i]);

    for (int i = ARRAY_LENGTH - 1; i > 0; i--)
        for (int j = 0; j < i; j++)
            if (numbers[j] > numbers[j + 1])
                swap(&numbers[j], &numbers[j + 1]);

    for (int i = 0; i < ARRAY_LENGTH; i++)
        printf("%d\n", numbers[i]);

    return 0;
}

void swap(int* from, int* to)
{
    int temp = *from;
    *from = *to;
    *to = temp;
}
