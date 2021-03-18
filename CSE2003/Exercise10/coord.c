#include <stdio.h>

int main(void)
{
    int x, y;

    printf("Enter x y: ");
    scanf("%d %d", &x, &y);

    if (x == 0 && y == 0)
        printf("(%d, %d) is on the origin.\n", x, y);
    else
        switch (y / x) {
        case 1:
            printf("(%d, %d) is on the line y = x.\n", x, y);
            break;

        case -1:
            printf("(%d, %d) is on the line y = -x.\n", x, y);
            break;

        default:
            if (x > 0 && y > 0)
                if (1.0f * y / x > 1)
                    printf("(%d, %d) is in region 1.\n", x, y);
                else
                    printf("(%d, %d) is in region 2.\n", x, y);
            else if (x > 0 && y < 0)
                if (1.0f * y / x > -1)
                    printf("(%d, %d) is in region 3.\n", x, y);
                else
                    printf("(%d, %d) is in region 4\n.", x, y);
            else if (x < 0 && y < 0)
                if (1.0f * y / x > 1)
                    printf("(%d, %d) is in region 5\n.", x, y);
                else
                    printf("(%d, %d) is in region 6\n.", x, y);
            else if (x < 0 && y > 0)
                if (1.0f * y / x > -1)
                    printf("(%d, %d) is in region 7\n.", x, y);
                else
                    printf("(%d, %d) is in region 8\n.", x, y);

            break;
        }

    return 0;
}
