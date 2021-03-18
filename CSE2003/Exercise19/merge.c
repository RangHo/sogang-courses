#include <stdio.h>

#define MAX_FILENAME 255
#define NUMBER_LIMIT 100

int main(void)
{
    char file1[MAX_FILENAME];
    char file2[MAX_FILENAME];
    printf("Input 1st file name: ");
    scanf("%s", file1);
    printf("Input 2nd file name: ");
    scanf("%s", file2);

    FILE *candid1, *candid2, *output;

    candid1 = fopen(file1, "r");
    candid2 = fopen(file2, "r");
    output = fopen("output.txt", "w");

    int number1[NUMBER_LIMIT] = { 0xdeadbeef };
    int number2[NUMBER_LIMIT] = { 0xdeadbeef };

    int input1, input2, count1, count2;
    for (count1 = 0; fscanf(candid1, "%d", &input1) && !feof(candid1); count1++)
        number1[count1] = input1;
    for (count2 = 0; fscanf(candid2, "%d", &input2) && !feof(candid2); count2++)
        number2[count2] = input2;

    int index1 = 0, index2 = 0, smaller;
    while (index1 < count1 && index2 < count2) {
        if (number1[index1] < number2[index2]) {
            smaller = number1[index1];
            index1++;
        } else {
            smaller = number2[index2];
            index2++;
        }
        fprintf(output, "%d ", smaller);
    }

    if (index1 < count1)
        for (/* index1 */; index1 < count1; index1++)
            fprintf(output, "%d ", number1[index1]);
    else if (index2 < count2)
        for (/* index2 */; index2 < count2; index2++)
            fprintf(output, "%d ", number2[index2]);

    return 0;
}
