#include <math.h>
#include <stdio.h>

int main(){
    float a,b,c,d;
    int A,B,C,D;

    printf("Enter 4 floats between 0 and 20.\n");
    scanf("%f %f %f %f", &a, &b, &c, &d);
    printf("\n");

    if(a < 0 || b < 0 || c < 0 || d < 0 || a > 20 || b > 20 || c > 20 || d > 20){
        printf("Enter values within range.");
        return 1;
    }

    A = (int)round(a);
    B = (int)round(b);
    C = (int)round(c);
    D = (int)round(d);

    for(int i = 0; i < A; i++){
        printf("*   ");
    }
    printf("%f\n", a);

    for(int i = 0; i < B; i++){
        printf("*   ");
    }
    printf("%f\n", b);

    for(int i = 0; i < C; i++){
        printf("*   ");
    }
    printf("%f\n", c);

    for(int i = 0; i < D; i++){
        printf("*   ");
    }
    printf("%f\n", d);

    return 0;
}