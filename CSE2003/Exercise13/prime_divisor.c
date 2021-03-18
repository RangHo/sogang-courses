#include <stdio.h>

int IsDivisor(int, int);
int IsPrime(int);

int main(void)
{
    int n;

    printf("Input n: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        if (IsDivisor(i, n) && IsPrime(i))
            printf("%d\t", i);
        else
            continue;
    }
    printf("\n");

    return 0;
}

int IsDivisor(int m, int n) { return (n % m) == 0; }

int IsPrime(int n)
{
    if (n == 1)
        return 0;

    for (int i = 2; i < n; i++) {
        if (n % i == 0)
            return 0;
        else
            continue;
    }

    return 1;
}
