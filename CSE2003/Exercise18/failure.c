#include <stdio.h>

int main(void)
{
    char name[6];
    float midterm, final;

    FILE* students = fopen("input33.txt", "r");

    float average = 0.0f;

    int count = 0;
    while (fscanf(students, "%s %f %f\n", name, &midterm, &final) && !feof(students)) {
        average += midterm + final;
        count++;
    }

    average /= count * 2;

    fclose(students);

    students = fopen("input33.txt", "r");
    FILE* output = fopen("output33.txt", "w");

    fprintf(output, "Name\t\tAverage\tPass/Fail\n");

    float student_average;

    while (fscanf(students, "%s %f %f\n", name, &midterm, &final) && !feof(students)) {
        student_average = (midterm + final) / 2;
        fprintf(output, "%s\t\t%.2f\t", name, student_average);
        if (student_average >= average)
            fprintf(output, "Pass\n");
        else
            fprintf(output, "Fail\n");
    }

    fprintf(output, "Average: %.2f", average);

    fclose(output);
    fclose(students);

    return 0;
}
