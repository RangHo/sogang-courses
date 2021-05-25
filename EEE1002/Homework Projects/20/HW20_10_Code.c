#include <stdio.h>

int main()
{
    FILE *f1, *f2;

    int n;

    f1 = fopen("20201510_Chanhyuk_Rhee_HW20_10_Source.txt", "r");
    f2 = fopen("20201510_Chanhyuk_Rhee_HW20_10_Output.txt", "w");

    while (feof(f1) == 0) {
        fscanf(f1, "%d", &n);
        fprintf(f2, "%d^2 = ", n);
        n = n * n;
        fprintf(f2, "%d\n", n);
    }
    fclose(f1);
    fclose(f2);

    printf("\nDone.");

    return 0;
}
