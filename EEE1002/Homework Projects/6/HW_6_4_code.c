#include <math.h>
#include <stdio.h>

int main()
{
    int n = 0;
    double rad;

    printf("_____________________\n");
    printf("|  x  | Sin  | Cos  |\n");
    printf("|-----|------|------|\n");

    while (n <= 180) {

        rad = n * 0.0174533;

        if (n == 0) {
            printf("|  ");
        } else if (n < 100) {
            printf("| ");
        } else {
            printf("|");
        }

        printf(" %d | %.2lf | %.2lf |\n", n, sin(rad), cos(rad));

        n += 15;
    }
    printf("---------------------\n");
    return 0;
}