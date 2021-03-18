#include <stdio.h>

float Sum(int*);

int main(void)
{
    char* student_name[10][255] = { 0 };
    float student_grade[10] = { 0.0f };

    FILE* data = fopen("input.txt", "r");

    int student_count;
    fscanf(data, "%d\n", &student_count);

    for (int i = 0; i < student_count; i++) {
        fscanf(data, "%s ", student_name[i]);
    }

    int grade_cache[5];
    for (int i = 0; i < student_count; i++) {
        fscanf(data, "%d %d %d %d %d\n", (int*)grade_cache, (int*)(grade_cache + 1),
            (int*)(grade_cache + 2), (int*)(grade_cache + 3), (int*)(grade_cache + 4));
        student_grade[i] = Sum(grade_cache);
    }

    fclose(data);

    FILE* out = fopen("out.txt", "w");

    for (int i = 0; i < student_count; i++)

        fprintf(out, "%s의 최종 점수는 %.2f\n", student_name[i], student_grade[i]);

    fclose(out);

    return 0;
}

float Sum(int* input)
{
    // [0]  [1]  [2]  [3]  [4]
    // 15%  40%  20%  20%  5%

    return input[0] * 0.15f + input[1] * 0.40f + input[2] * 0.20f + input[3] * 0.20f
        + input[4] * 0.05f;
}
