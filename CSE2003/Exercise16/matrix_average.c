#include <stdio.h>

float MatrixAverage(int*, int, int);

int main(void)
{
    int size;
    scanf("%d", &size);

    int matrix[size][size];
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            scanf("%d", &matrix[i][j]);

    for (int i = 0; i < size; i++)
        printf("%0.2f \t", MatrixAverage((int*)matrix, i, size));

    printf("\n");

    return 0;
}

float MatrixAverage(int* matrix, int column_index, int size)
{
    float result = 0.0f;

    for (int i = 0; i < size; i++)
        result += *((matrix + (i * size)) + column_index);

    return result / size;
}
