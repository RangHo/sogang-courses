#include <stdio.h>

int main()
{
    char line[100], character;
    int c = 0;
    printf("Enter Your name.\n");
    do {
        character = getchar();
        line[c] = character;
        c++;
    } while (character != '\n');

    c = c - 1;

    line[c] = '\0';

    printf("\nYour name in ASCII value:\n");

    for (int i = 0; i < c; i++) {
        printf("%d.", line[i]);
    }

    return 0;
}