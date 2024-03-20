#include <math.h>
#include <stdio.h>

double a, b, c, disc, r1, r2;

int main()
{
    printf("Enter a, b, c: \n");
    scanf("%lf %lf %lf", &a, &b, &c);

    //--------------------------------------------------
    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                printf("Constant function. Every real number ia a root.\n");
            } else {
                printf("Constant function. Root does not exist.\n");
            }
        } else {
            r1 = -(c / b);
            printf("Root : %.3lf \n", r1);
        }
        return 0;
    }
    //--------------------------------------------------

    disc = (b * b) - (4 * a * c);

    if (disc >= 0) {
        r1 = (-b + sqrt(disc)) / (2 * a);
        r2 = (-b - sqrt(disc)) / (2 * a);

        if (r1 == r2) {
            printf("Double Root. Root : %.3lf \n", r1);
        }

        else {
            printf("Root 1 : %.3lf , Root 2 : %.3lf \n", r1, r2);
        }
    }
    //--------------------------------------------------
    else {
        printf("Root is imaginary and does not exist.");
    }
    return 0;
}