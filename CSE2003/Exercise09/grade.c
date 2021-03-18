#include <stdio.h>

float avgFunc(float, float, float);
void gradeFunc(float);

int main(void)
{
    float first, second, third;
    printf("Enter three grades: ");
    scanf("%f %f %f", &first, &second, &third);

    gradeFunc(avgFunc(first, second, third));

    return 0;
}

float avgFunc(float one, float two, float three) { return (one + two + three) / 3; }

void gradeFunc(float average)
{
    if (average >= 50)             // D
        if (average >= 70)         // C
            if (average >= 80)     // B
                if (average >= 90) // A
                    printf("Grade: A\n");
                else
                    printf("Grade: B\n");
            else
                printf("Grade: C\n");
        else
            printf("Grade: D\n");
    else
        printf("Grade: F\n");
}
