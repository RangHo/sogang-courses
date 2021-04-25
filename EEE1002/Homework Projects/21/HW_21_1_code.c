#include<stdio.h>

int main(){
    FILE *f1;
    char c;
    printf("Data Input\n\n");

    //Open File

    f1 = fopen("INPUT", "w");
    
    while((c = getchar()) != EOF){
        putc(c,f1); //Write to INPUT
    }

    fclose(f1);

    printf("\nData Output\n\n");

    //reopen file, read mode
    f1 = fopen("INPUT", "r");

    while((c = getc(f1)) != EOF){
        printf("%c", c);
    }
    fclose (f1);


}