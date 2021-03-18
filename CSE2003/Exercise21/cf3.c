#include <stdio.h>

int main(void)
{
    int size, number;
    scanf("%d %d", &size, &number);

    int set[256];

    for (int i = 0; i < size; i++)
        scanf("%d", &set[i]);

    int count = 0;

    int sum = 0;
    for (int flag = 0; flag <= (1 << size); flag++) {
        for (int index = 0; index < size; index++)
            if (flag & (1 << index))
                sum += set[index];

        if (sum == number)
            count++;

        sum = 0;
    }

    printf("The number of subsets: %d\n", count);

    return 0;
}
