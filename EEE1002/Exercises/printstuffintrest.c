#include <stdio.h>

int main(){
    int year, period;
    float amount, inrate, value;

    printf("Input amount, interst rate, and period.\n\n");
    scanf("%f %f %d", &amount, &inrate, &period);
    printf("\n");
    year = 1;

    for(; year <= period; year++){
        printf("%2d Rs %8.2f\n", year, value= amount + inrate * amount);
        amount = value; 
    }


}