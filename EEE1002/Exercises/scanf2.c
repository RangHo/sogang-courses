#include <stdio.h>


int main(){

    while (1){
    int number;
    printf("Enter an interger.\n");
    scanf("%d", &number);

        if(number < 100){
            printf("\nyour number is smaller than 100.\n");
        }
        else{
            printf("\nyour number has more than 2 digits.\n");
        }
    }

    return 0;

}