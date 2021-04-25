#include<stdio.h>

int main(){
    FILE *f1;

    int n;
    int sum = 0;

    f1 = fopen("20201510_Chanhyuk_Rhee_HW20_9.txt","r");
    while(feof(f1) == 0){
        fscanf(f1, "%d", &n);
        sum += n;
    }
    fclose(f1);

    f1 = fopen("20201510_Chanhyuk_Rhee_HW20_9.txt","a");
    fprintf(f1, " %d", sum);
    fclose(f1);

    printf("\nDone. Sum: %d", sum);

    return 0;
}
