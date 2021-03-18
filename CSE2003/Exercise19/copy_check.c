#include <stdio.h>

#define MAX_FILENAME 256

int main(void)
{
    char file1[MAX_FILENAME];
    char file2[MAX_FILENAME];
    printf("Input 1st file name: ");
    scanf("%s", file1);
    printf("Input 2nd file name: ");
    scanf("%s", file2);

    FILE *candid1, *candid2;

    candid1 = fopen(file1, "r");
    candid2 = fopen(file2, "r");

    char cache1, cache2;
    int total = 0;
    int same = 0;
    while (!feof(candid1) && !feof(candid2)) {
        do {
            if (feof(candid1))
                break;
            cache1 = fgetc(candid1);
        } while (cache1 == ' ' || cache1 == '\n');

        do {
            if (feof(candid2))
                break;
            cache2 = fgetc(candid2);
        } while (cache2 == ' ' || cache2 == '\n');

        if (cache1 == EOF || cache2 == EOF)
            break;

        if (cache1 == cache2)
            same++;

        total++;
    }

    printf("Total: %d\n", total);
    printf("Same: %d\n", same);
    printf("Copy Ratio: %.3f%%\n", 100.0f * same / total);

    fclose(candid1);
    fclose(candid2);

    return 0;
}
