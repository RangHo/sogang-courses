#include <stdio.h>

int main(){
    float num;
    int n;

    printf("Enter a float.\n");
    scanf("%f", &num);
    n = (int)num;
    n = n % 10;

    printf("Right most digit of integral part: %d", n);
    return 0;
}