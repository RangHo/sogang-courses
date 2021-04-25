#include <stdio.h>

void printline();
int main(){
    printline();
    printf("This illustrates the use of C functions\n");
    printline();

    return 0;
}

void printline(){
    int i;
    for(i = 1; i < 40; i++){
        printf("-");
    }
    printf("\n");
}