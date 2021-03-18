#include <stdio.h>

float get_average(int, int, int, int);
float get_deviation(float, int);

int main(void)
{
    int one, two, three, four;

    printf("Enter the first number: ");
    scanf("%d", &one);
    printf("Enter the second number: ");
    scanf("%d", &two);
    printf("Enter the third number: ");
    scanf("%d", &three);
    printf("Enter the fourth number: ");
    scanf("%d", &four);

    float average = get_average(one, two, three, four);

    printf("******** Average: %f ********\n", average);

    printf("First number:\t %5d -- Deviation: %8.2f\n", one, get_deviation(average, one));
    printf("Second number:\t %5d -- Deviation: %8.2f\n", two, get_deviation(average, two));
    printf("Third number:\t %5d -- Deviation: %8.2f\n", three, get_deviation(average, three));
    printf("Fourth number:\t %5d -- Deviation: %8.2f\n", four, get_deviation(average, four));

    return 0;
}

float get_average(int a, int b, int c, int d) { return (a + b + c + d) / 4.0f; }

float get_deviation(float average, int target) { return target - average; }
