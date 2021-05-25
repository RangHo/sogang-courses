#include <stdio.h>

struct marks {
    int sub1;
    int sub2;
    int sub3;
    int total;
};

int main()
{
    int i;
    struct marks student[3] = { { 45, 67, 81, 0 }, { 75, 53, 69, 0 }, { 57, 36, 71, 0 } };
    struct marks total = { 0, 0, 0, 0 };

    for (i = 0; i <= 2; i++) {
        student[i].total = student[i].sub1 + student[i].sub2 + student[i].sub3;

        total.sub1 = total.sub1 + student[i].sub1;
        total.sub2 = total.sub2 + student[i].sub2;
        total.sub3 = total.sub3 + student[i].sub3;
        total.total = total.total + student[i].total;
    }

    printf("Student   Total");
    for (i = 0; i <= 2; i++) {
        printf("\nStudent[%d] %d", i + 1, student[i].total);
    }
    printf("\n\nSubject   Total\n");
    printf("%s %d\n%s %d\n%s %d\n", "Subject 1 ", total.sub1, "Subject 2 ", total.sub2,
        "Subject 3 ", total.sub3);

    printf("\nGrand Total : %d\n\n", total.total);

    return 0;
}