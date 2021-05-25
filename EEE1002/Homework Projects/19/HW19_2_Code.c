#include <stdio.h>
int main()
{
    char* name;
    int length;
    name = "DELHI";
    char* cptr = name;

    printf("%s\n", name);

    while (*cptr != '\0') {
        printf("%c is stored at address %u\n", *cptr, cptr);
        cptr++;
    }

    length = cptr - name;
    printf("\nLength of string: %d\n", length);

    return 0;
}