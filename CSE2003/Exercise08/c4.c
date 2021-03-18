#include <stdio.h>

char Grade(int, int, int);

int main(void)
{
    int first, second, third;
    scanf("%d %d %d", &first, &second, &third);

    printf("Grade is %c.", Grade(first, second, third));

    return 0;
}

char Grade(int first, int second, int third)
{
    float total = first * 0.2f + second * 0.3f + third * 0.5f;

    return 'D' - (char)(total / 30);
}
