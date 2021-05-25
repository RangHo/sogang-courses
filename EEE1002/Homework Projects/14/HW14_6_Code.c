#include <stdio.h>

int poly(int a[], int, int);

int main()
{
    int x, n;
    printf("Enter order of polynomial.\n");
    scanf("%d", &n);
    printf("Enter x.\n");
    scanf("%d", &x);

    int arr[n + 1];

    printf("Enter a_0 ~ a_%d\n", n);
    for (int i = 0; i < n + 1; i++) {
        scanf("%d", &arr[i]);
    }

    printf("\nThe value of the polynomial is %d", poly(arr, n, x));

    return 0;
}

int poly(int a[], int n, int x)
{
    int ans = a[0];
    for (int i = 0; i < n; i++) {
        ans = ans * x + a[i + 1];
    }
    return ans;
}