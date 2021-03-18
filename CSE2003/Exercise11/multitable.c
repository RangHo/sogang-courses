#include <stdio.h>

int main(void)
{
    int num;

    scanf("%d", &num);

    int index = 1;

    while (index <= 9) {
        printf("%d * %d = %d\n", num, index, num * index);
        index++;
    }

    return 0;
}
