#include <stdio.h>

int i = 0;
int pos = 0;
int neg = 0;

int main(){
    printf("Enter positive or negative numbers. Enter '0' to end.\n");

    while(1){
        scanf("%d", &i);
        if(i>0){
            pos++;
        }

        else if(i<0){
            neg++;
        }

        else if(i == 0){
            break;
        }
    }

    printf("N. of positive numbers : %d\n", pos);
    printf("N. of negative numbers : %d\n\n", neg);

    return 0;
}