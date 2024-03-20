#include <math.h>
#include <stdio.h>

int main()
{
    float a, b, c, d;
    int A, B, C, D;

    printf("Enter the following numbers:\n35.7, 50.21, -23.73, -46.45\n");
    scanf("%f %f %f %f", &a, &b, &c, &d);

    A = (int)round(a);
    B = (int)round(b);
    C = (int)round(c);
    D = (int)round(d);

    printf("\n%d, %d, %d, %d", A, B, C, D);

    return 0;
}