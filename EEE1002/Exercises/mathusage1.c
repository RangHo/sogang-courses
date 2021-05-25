#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.1416
#define MAX 180

int main()
{
    int angle = 0;
    float x = 0.0;
    float y = 0.0;

    printf("Angle Cos(angle)\n\n");

    while (angle <= MAX) {
        x = (PI / MAX) * angle;
        y = cos(x);
        printf("%15d %13.4f\n", angle, y);
        angle = angle + 10;
    }

    return 0;
}