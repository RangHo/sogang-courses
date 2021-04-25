#include<stdio.h>

int* day_name(int n);

int main(){
    int num;
    int* ptr;

    printf("\nEnter a number: ");
    scanf("%d", &num);

    num--;

    if(num < 0 || num > 6){
        printf("\nError: Please Enter Valid Date.\n\n");
        return 1;
    }

    ptr = day_name(num);
    
    printf("\nEntered Day: %s\n\n", *ptr);
    return 0;
}

int* day_name(int n){   
    static char* names[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}; 
    return(int*)&names[n];
}