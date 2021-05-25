#include <stdio.h>

int num[10][10] = { 0 };

int main()
{

    for (int i = 0; i < 10; i++) {
        num[i][0] = 1;
        num[i][i] = 1;
    }

    for (int i = 2; i < 10; i++) {
        for (int j = 1; j < i; j++) {
            num[i][j] = num[i - 1][j - 1] + num[i - 1][j];
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%d ", num[i][j]);
        }
        printf("\n");
    }

    return 0;
}