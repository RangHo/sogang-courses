#include <stdio.h>

void ToUpper(char*);

int main(void)
{
    char sentence[50] = { 0 };

    for (int i = 0; i < 50; i++) {
        scanf("%c", (char*)(sentence + i));
        if (sentence[i] == '\n')
            break;
    }

    ToUpper(sentence);

    printf("%s\n", sentence);

    return 0;
}

void ToUpper(char* sentence)
{
    for (int i = 0; i < 50; i++)
        if (sentence[i] >= 'a' && sentence[i] <= 'z')
            sentence[i] = sentence[i] - 32;
}
