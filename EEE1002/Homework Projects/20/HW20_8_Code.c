#include <stdio.h>

int main()
{
    FILE *f1, *f2;
    char c;

    f1 = fopen("20201510_Chanhyuk_Rhee_HW20_8_Source.txt", "r");
    f2 = fopen("20201510_Chanhyuk_Rhee_HW20_8_Output.txt", "w");

    c = fgetc(f1);
    while (c != EOF) {
        fputc(c, f2);
        c = fgetc(f1);
    }

    printf("\nDone.\n");

    fclose(f1);
    fclose(f2);

    return 0;
}
