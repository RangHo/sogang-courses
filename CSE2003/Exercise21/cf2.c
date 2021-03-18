#include <stdio.h>

int main(void)
{
    int matrix[4] = { 1, 1, 1, 0 }; // Flattened matrix

    int a11 = 1, a12 = 1;
    int a21 = 1, a22 = 0;

    int a11p, a12p;
    int a21p, a22p;

    int power;
    scanf("%d", &power);

    for (int i = 0; i < power - 1; i++) {
        a11p = a11;
        a12p = a12;
        a21p = a21;
        a22p = a22;

        a11 = a11p + a12p;
        a12 = a11p;
        a21 = a21p + a22p;
        a22 = a21p;
    }

    printf("%d\n", a12);

    return 0;
}
