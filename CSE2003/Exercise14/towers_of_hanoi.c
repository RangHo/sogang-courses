#include <stdio.h>

void SolveTowerOfHanoi(int, char, char, char);
void PrintStep(char, char);

int main(void)
{
    int disks;

    printf("How many disks are there? ");
    scanf("%d", &disks);

    SolveTowerOfHanoi(disks, 'S', 'A', 'D');

    return 0;
}

void SolveTowerOfHanoi(int disk, char source, char auxilary, char destination)
{
    if (disk == 1) {
        PrintStep(source, destination);
        return;
    } else {
        SolveTowerOfHanoi(disk - 1, source, destination, auxilary);
        PrintStep(source, destination);
        SolveTowerOfHanoi(disk - 1, auxilary, source, destination);
    }
}

void PrintStep(char from, char to) { printf("Move a disk from %c to %c.\n", from, to); }
