#include <stdio.h>

#define ROWS 9
#define COLUMNS 9

int main()
{
    int column, product[ROWS][COLUMNS];

    printf("   ");
    for (int j = 2; j <= COLUMNS; j++) {
        printf("%4d", j);
    }
    printf("\n");
    printf("-------------------------------------\n");

    for (int i = 1; i < ROWS; i++) {
        printf("%2d |", (i + 1));

        for (int j = 2; j <= COLUMNS; j++) {

            int k = j;

            product[i][j] = (i + 1) * j;
            printf("%4d", product[i][j]);
        }
        printf("\n");
    }

    return 0;
}
