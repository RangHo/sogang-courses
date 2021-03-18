#include <stdio.h>

float avgFunc(float, float, float);
char gradeFunc(float);
char gradeDetailFunc(char, float);

int main(void)
{
    float first, second, third;
    printf("Input: ");
    scanf("%f %f %f", &first, &second, &third);

    float average = avgFunc(first, second, third);
    char grade = gradeFunc(average);
    char detailed_grade = gradeDetailFunc(grade, average);

    printf("Score: %5.2f\n", average);
    printf("Grade: %c%c\n", grade, detailed_grade);

    return 0;
}

float avgFunc(float one, float two, float three) { return (one + two + three) / 3; }

char gradeFunc(float average)
{
    if (average >= 50)             // D
        if (average >= 70)         // C
            if (average >= 80)     // B
                if (average >= 90) // A
                    return 'A';
                else
                    return 'B';
            else
                return 'C';
        else
            return 'D';
    else
        return 'F';
}

char gradeDetailFunc(char grade, float average)
{
    if (grade == 'F')
        return ' ';

    int lower = (int)average % 10;

    if (lower >= 3)
        if (lower >= 7)
            return '+';
        else
            return '0';
    else
        return '-';
}
