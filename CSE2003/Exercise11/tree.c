#include <stdio.h>

int main(void)
{
    int count;

    printf("Input: ");
    scanf("%d", &count);

    int level, left, star, right;

    level = count;
    while (level > 0) {
        left = 0;
        while (left < level - 1) {
            printf(" ");
            left++;
        }

        star = 0;
        while (star < 2 * (count - level)) {
            printf("*");
            star++;
        }
        printf("*");

        right = 0;
        while (right < level - 1) {
            printf(" ");
            right++;
        }

        level--;

        printf("\n");
    }

    return 0;
}
