#include <stdio.h>

int factorial(int);

int main(){
    int n = 0;

    printf("Enter number: ");
    scanf("%d", &n);
    printf("\nFactorial of %d is %d.\n\n", n, factorial(n));
}

int factorial(int n){
    int fact;
    if(n == 1){
        return 1;
    }
    else{
        fact = n*factorial(n-1);
    }

    return (fact);
}