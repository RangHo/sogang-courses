#include <stdio.h>

int cast_and_multiply(int, float);
int multiply_and_cast(int, float);

int main(void)
{
    int a;
    float b;

    scanf("%d %f", &a, &b);

    printf("Cast and multiply: %d\n", cast_and_multiply(a, b));
    printf("Multiply and cast: %d\n", multiply_and_cast(a, b));

    return 0;
}

int cast_and_multiply(int left, float right) { return left * (int)right; }

int multiply_and_cast(int left, float right) { return (int)(left * right); }
