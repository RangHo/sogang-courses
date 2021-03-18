#include <stdio.h>

char x, y;

void NextChar(char*, char*);
void PrintResult(char, char);

int main(void)
{
    printf("Enter two characters [A-T]: ");
    scanf("%c %c", &x, &y);

    PrintResult(x, y);

    return 0;
}

void NextChar(char* a, char* b)
{
    x = *a;
    y = *b;

    *a += 1;
    *b += 2;
}

void PrintResult(char a, char b)
{
    NextChar(&a, &b);
    printf("%c -> %c, %c -> %c\n", x, a, y, b);
    NextChar(&a, &b);
    printf("%c -> %c, %c -> %c\n", x, a, y, b);
    NextChar(&a, &b);
    printf("%c -> %c, %c -> %c\n", x, a, y, b);
}
