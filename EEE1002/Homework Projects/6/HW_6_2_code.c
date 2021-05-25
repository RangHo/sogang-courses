#include <math.h>
#include <stdio.h>

int main()
{
    int n = 0, nc = 0, ans = 0, count = 0, mod = 0;

    printf("Enter an integer : \n");
    scanf("%d", &n);

    nc = n;

    while (nc != 0) {
        nc = nc / 10;
        count++;
    }

    printf("\nOutput: \n");
    while (count > 0) {

        mod = n % ((int)pow(10, count));

        printf("%d\n", mod);

        count--;
    }
    return 0;
}