#include <stdio.h>

void MultiplyMatrices(int[][4][4]);

int main(void)
{
    int matrices[3][4][4] = { 0 };

    printf("First Matrix:\n");
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            scanf("%d", &matrices[0][i][j]);

    printf("\n");

    printf("Second Matrix:\n");
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            scanf("%d", &matrices[1][i][j]);

    MultiplyMatrices(matrices);

    printf("\n");

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            printf("%d\t", matrices[2][i][j]);

        printf("\n");
    }

    return 0;
}

void MultiplyMatrices(int matrices[][4][4])
{
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++)
            for (int i = 0; i < 4; i++)
                matrices[2][x][y] += matrices[0][x][i] * matrices[1][i][y];
}
