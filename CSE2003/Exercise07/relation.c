#include <stdio.h>

int main(void)
{
    float value;

    printf("Input a decimal value: ");
    scanf("%f", &value);

    printf("Use '>': %d\n", (int)(value + 0.5) > value);
    printf("Use '>=': %d\n", value >= ((int)value + 0.5));
    printf("Use '==': %d\n", (int)value + 1 == (int)(value + 0.5));
    printf("Use '!=': %d\n", (int)value != (int)(value + 0.5));

    return 0;
}
