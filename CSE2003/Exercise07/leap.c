#include <stdio.h>

int main(void)
{
    int year;

    printf("Enter the year to be tested: ");
    scanf("%d", &year);

    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        printf("It is a leap year.\n");
    } else {
        printf("It is not a leap year.\n");

        int closest = year - 1;
        closest -= closest % 4;
        if (closest % 100 == 0 && year % 400 != 0) {
            closest -= 1;
            closest -= closest % 4;
        }
        printf("%d is a leap year.", closest);
    }

    return 0;
}
