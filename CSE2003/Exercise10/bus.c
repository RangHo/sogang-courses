#include <stdio.h>

int main(void)
{
    int hour, minute;
    printf("What time is it? ");
    scanf("%d:%d", &hour, &minute);

    int total_minutes = hour * 60 + minute - 5 * 60;
    int buses_available = total_minutes / 20;

    if (total_minutes < 0 || total_minutes > 1120) {
        printf("No buses are available.");
        return 0;
    }

    switch (buses_available % 5) {
    case 0:
        if (total_minutes % 20 == 0)
            printf("Bus #1 is approaching!");
        else
            printf("Bus #2 is approaching!");
        break;
    case 1:
        if (total_minutes % 20 == 0)
            printf("Bus #2 is approaching!");
        else
            printf("Bus #3 is approaching!");
        break;
    case 2:
        if (total_minutes % 20 == 0)
            printf("Bus #3 is approaching!");
        else
            printf("Bus #4 is approaching!");
        break;
    case 3:
        if (total_minutes % 20 == 0)
            printf("Bus #4 is approaching!");
        else
            printf("Bus #5 is approaching!");
        break;
    case 4:
        if (total_minutes % 20 == 0)
            printf("Bus #5 is approaching!");
        else
            printf("Bus #1 is approaching!");
        break;
    }

    return 0;
}
