#include <stdio.h>

int main(void)
{
    int length;

    scanf("%d", &length);

    int orig[length];
    int squared[length];
    int cubed[length];

    for (int i = 0; i < length; i++) {
        orig[i] = i + 1;
        squared[i] = orig[i] * orig[i];
        cubed[i] = squared[i] * orig[i];
    }

    for (int i = 0; i < length; i++) {
        printf("%d ", orig[i]);
    }
    printf("\n");

    for (int i = 0; i < length; i++) {
        printf("%d ", squared[i]);
    }
    printf("\n");

    for (int i = 0; i < length; i++) {
        printf("%d ", cubed[i]);
    }
    printf("\n");

    return 0;
}
