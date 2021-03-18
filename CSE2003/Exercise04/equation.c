#include <stdio.h>

float get_x(int, int, int, int);
float get_y(int, int, int, int);

int main(void)
{
    int a, b, c, d;
    // y = ax - b
    // y = cx - d

    printf("1st equation (y = ax - b) -- input 'a' and 'b'.\n");
    printf("a = ");
    scanf("%d", &a);
    printf("b = ");
    scanf("%d", &b);

    printf("2nd equation (y = cx - d) -- input 'c' and 'd'.\n");
    printf("c = ");
    scanf("%d", &c);
    printf("d = ");
    scanf("%d", &d);

    printf("==========\n");

    printf("Result\n");
    printf("x is %f\n", get_x(a, b, c, d));
    printf("y is %f\n", get_y(a, b, c, d));

    return 0;
}

float get_x(int a, int b, int c, int d)
{
    // ax - b = cx - d
    // (a - c)x = b - d
    // x = (b - d) / (a - c)

    return (b - d) * 1.0f / (a - c);
}

float get_y(int a, int b, int c, int d) { return a * get_x(a, b, c, d) - b; }
