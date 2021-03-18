#include <stdio.h>

int main(void)
{
    int birthday, year, month, day;

    printf("Birthday (YYYYMMDD): ");
    scanf("%d", &birthday);

    year = birthday / 10000;
    birthday %= 10000;
    month = birthday / 100;
    birthday %= 100;
    day = birthday;

    printf("Your birthday is %d / %d / %d\n", year, month, day);

    int present;

    printf("This year (YYYY): ");
    scanf("%d", &present);

    printf("In %d, your age is %d.\n", present, present - year + 1);

    return 0;
}
