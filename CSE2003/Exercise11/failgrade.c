#include <stdio.h>

int main(void)
{
    int number, cutline;
    int total = 0;
    int failures = 0;
    int index = 0;

    printf("Number of classes: ");
    scanf("%d", &number);

    printf("Cutline: ");
    scanf("%d", &cutline);

    while (index < number) {
        int score;

        printf("Input score #%d: ", index);
        scanf("%d", &score);

        if (score < cutline)
            failures++;

        total += score;

        index++;
    }

    printf("Average: %.2f\nNumber of failues: %d\n", 1.0f * total / number, failures);

    return 0;
}
