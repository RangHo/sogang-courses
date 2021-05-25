#include <stdio.h>

int main()
{
    int n = 1;
    for (int i = 0; n < 91; i++) {
        for (int j = 0; j < i; j++) {
            printf("%d ", (n++) % 2);
        }
        printf("\n");
    }
}