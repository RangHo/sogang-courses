#include <stdio.h>

int IsOverlapped(int*, int*);

int main(void)
{
    FILE* input = fopen("input35.txt", "r");
    FILE* output = fopen("output35.txt", "w");

    int testcases;
    fscanf(input, "%d\n", &testcases);

    int rect1[4] = { 0 };
    int rect2[4] = { 0 };

    for (int i = 0; i < testcases; i++) {
        fscanf(input, "%d %d %d %d\n", rect1, rect1 + 1, rect1 + 2, rect1 + 3);
        fscanf(input, "%d %d %d %d\n", rect2, rect2 + 1, rect2 + 2, rect2 + 3);

        if (IsOverlapped(rect1, rect2))
            fprintf(output, "true\n");
        else
            fprintf(output, "false\n");
    }

    fclose(input);
    fclose(output);

    return 0;
}

int IsOverlapped(int rect1[4], int rect2[4])
{
    int // Just for me to understand better
        r1_x1
        = rect1[0],
        r1_y1 = rect1[1], r1_x2 = rect1[2], r1_y2 = rect1[3];

    int r2_x1 = rect2[0], r2_y1 = rect2[1], r2_x2 = rect2[2], r2_y2 = rect2[3];

    if (r2_x1 >= r1_x1 && r2_x1 <= r1_x2 && r2_y2 >= r1_y1 && r2_y2 <= r1_y2)
        return 1;
    else if (r1_x1 >= r2_x1 && r1_x1 <= r2_x2 && r1_y2 >= r2_y1 && r1_y2 <= r2_y2)
        return 1;
    else if (r1_x2 >= r2_x1 && r1_x2 <= r2_x2 && r1_y2 >= r2_y1 && r1_y2 <= r2_y2)
        return 1;
    else if (r2_x2 >= r1_x1 && r2_x2 <= r1_x2 && r2_y2 >= r1_y1 && r2_y2 <= r1_y2)
        return 1;

    return 0;
}
