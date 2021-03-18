#include <stdio.h>

#define ALPHABET_NUMBER 26

int IsAlphabet(char);
char ToLower(char);

int main(void)
{
    FILE* text = fopen("text.txt", "r");

    int occurances[ALPHABET_NUMBER] = { 0 };

    char target;
    do {
        target = fgetc(text);

        if (!IsAlphabet(target))
            break;

        (*(occurances + (ToLower(target) - 'a')))++;
    } while (target != EOF);

    for (int i = 0; i < ALPHABET_NUMBER; i++)
        printf("%c: %d\t", 'A' + i, occurances[i]);

    printf("\n");

    return 0;
}

int IsAlphabet(char target)
{
    return (target >= 'A' && target <= 'Z') || (target >= 'a' && target <= 'z');
}

char ToLower(char target)
{
    if (target >= 'A' && target <= 'Z')
        return target - ('a' - 'A') + 1;
    else
        return target;
}
