#include <stdio.h>

int main(void)
{
    char source_name[30], destination_name[30];

    printf("Enter source file: ");
    scanf("%s", source_name);

    printf("Enter destination file: ");
    scanf("%s", destination_name);

    FILE* src = fopen(source_name, "r");
    FILE* dest = fopen(destination_name, "w");

    while (!feof(src))
        fputc(fgetc(src), dest);

    fclose(src);
    fclose(dest);

    return 0;
}
