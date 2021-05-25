#include <stdio.h>

float dist = 0;
float gal = 0;
float ans = 0;

int main()
{
    printf("Enter miles traveled and gallons consumed. \n");
    scanf("%f %f", &dist, &gal);
    ans = dist / gal;
    printf("Fuel mileage : %.2f MPG or %2f Km/L", ans, (ans * 0.425144));

    return 0;
}