#include <stdio.h>

float Degree_to_Rad(float);
float Rad_to_Degree(float);

int main(void)
{
    float deg, rad;

    printf("Enter the size of an angle in degrees: ");
    scanf("%f", &deg);

    printf("Enter the size of an angle in radians: ");
    scanf("%f", &rad);

    double converted_rad = (double)Degree_to_Rad(deg);
    double converted_deg = (double)Rad_to_Degree(rad);

    printf("Degrees to radians: %8.3f\n", converted_rad);
    printf("Radians to degrees: %8.3f\n", converted_deg);

    return 0;
}

float Degree_to_Rad(float deg) { return deg / 57.2958f; }

float Rad_to_Degree(float rad) { return rad * 57.2958f; }
