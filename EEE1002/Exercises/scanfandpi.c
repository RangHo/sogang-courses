#include <stdio.h>
#define pi 3.141592

int main()
{
    double height, radius, base, volume;

    printf("Enter the height and radius of cone");
    scanf("%lf %lf", &height, &radius);

    base = pi * radius * radius;
    volume = (1.0 / 3.0) * base * height;

    printf("\n The volume of a cone is %f", volume);

    return 0;
}