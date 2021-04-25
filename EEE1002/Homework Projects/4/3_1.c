#include <stdio.h>

int main(){
    int n = 0;
    int i = 1;
    float ans = 0.0;

    printf("Enter an interger.\n>>");
    scanf("%d", &n);

    while(i <= n){
        ans = ans + ((float)1/i);
        i++;
    }
    printf("%f\n", ans);

    return 0;
}