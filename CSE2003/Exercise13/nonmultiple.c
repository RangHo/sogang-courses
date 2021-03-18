#include <stdio.h>
#define VERY_BIG_NUMBER 1000000000

int main(void)
{
    int n;
    int sum = 0;
    int i;

    printf("Input n: ");
    scanf("%d", &n);

    for (i = 1; i <= VERY_BIG_NUMBER; i++) {
        if (i % n != 0)
            sum += i;
        else
            continue;

        if (sum > VERY_BIG_NUMBER)
            break;
    }

    printf("%d\t%d\n", i, sum);
    return 0;
}
