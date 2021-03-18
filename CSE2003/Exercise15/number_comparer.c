#include <stdio.h>

int main(void)
{
    int a[5];
    int b[5];

    scanf("%d %d %d %d %d", &a[0], &a[1], &a[2], &a[3], &a[4]);
    scanf("%d %d %d %d %d", &b[0], &b[1], &b[2], &b[3], &b[4]);

    for (int i = 0; i < 5; i++) {
        if (a[i] != b[i]) {
            printf("false\n");
            return 0;
        }
    }

    printf("true\n");
    return 0;
}
