#include <stdio.h>

int main(){
    int a = 15, b = 10, c;

    c = ++a - b;

    printf("a = %d b = %d c = %d \n", a, b, c);

    int d = b++ +a;

    printf("a = %d b = %d d = %d \n", a, b, d);
    printf("a/b = %d\n", a/b);
    printf("a%%b = %d\n", a%b);
    printf("a *= b = %d\n", a*= b);
    printf("%d\n", (c>d) ? 1 : 0);
    printf("%d\n", (c<d) ? 1 : 0);

    return 0;
}

