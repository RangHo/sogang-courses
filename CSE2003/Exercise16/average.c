#include <stdio.h>

float GetAverage(int*, int);

int main(void)
{
    int length;
    printf("n?: ");
    scanf("%d", &length);

    int array[100] = { 0 };
    for (int i = 0; i < length; i++)
        scanf("%d", (int*)(array + i));

    printf("%.6f\n", GetAverage(array, length));

    return 0;
}

float GetAverage(int* array, int length)
{
    float result = 0.0f;

    for (int i = 0; i < length; i++)
        result += array[i];

    return result / length;
}
