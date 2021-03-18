#include <stdio.h>

int main(void)
{
    FILE* data = fopen("input.txt", "r");

    int size, number_size = 0;
    fscanf(data, "%d", &size);

    int numbers[100] = { 0 };
    int counts[100] = { 0 };

    int temp, changed = 0;
    for (int i = 0; i < size; i++) {
        fscanf(data, "%d ", &temp);

        for (int j = 0; j < size; j++) {
            if (numbers[j] == temp) {
                numbers[j] = temp;
                counts[j]++;
                changed = 1;
            }
        }

        if (!changed) {
            numbers[i] = temp;
            counts[i]++;
            number_size++;
        }

        changed = 0;
    }

    fclose(data);

    for (int i = 0; i < number_size - 1; i++) {
        for (int j = 0; j < number_size - (i + 1); j++) {
            if (counts[j] < counts[j + 1]) {
                temp = counts[j + 1];
                counts[j + 1] = counts[j];
                counts[j] = temp;

                temp = numbers[j + 1];
                numbers[j + 1] = numbers[j];
                numbers[j] = temp;
            } else if (counts[j] == counts[j + 1] && numbers[j] > numbers[j + 1]) {
                temp = counts[j + 1];
                counts[j + 1] = counts[j];
                counts[j] = temp;

                temp = numbers[j + 1];
                numbers[j + 1] = numbers[j];
                numbers[j] = temp;
            }
        }
    }

    data = fopen("output.txt", "w");

    for (int i = 0; i < number_size; i++)
        for (int j = 0; j < counts[i]; j++)
            fprintf(data, "%d ", numbers[i]);

    fclose(data);

    return 0;
}
