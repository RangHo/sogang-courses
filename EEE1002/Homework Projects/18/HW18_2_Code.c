#include<stdio.h>
int main(){
    int x, y;
    int* ptr;
    x = 10;
    ptr = &x;
    y = *ptr;

    printf("Value of x is %d\n\n", x);
    printf("%d is stored at addr %u\n", x, &x);
    printf("%d is stored at addr %u\n", *&x, &x);
    printf("%d is stored at addr %u\n", *ptr, ptr);
    printf("%d is stored at addr %u\n", ptr, &ptr);
    printf("%d is stored at addr %u\n", y, &y);

    *ptr = 25;
    printf("\nNow x = %d\n", x);

    return 0; 
}