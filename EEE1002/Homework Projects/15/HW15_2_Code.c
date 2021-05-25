#include <stdio.h>

void mathoperation(int x, int y, int* s, int* d);

int main()
{
    int x = 20, y = 10, s, d;
    mathoperation(x, y, &s, &d);
    printf("s = %d\nd = %d\n", s, d);

    return 0;
}

void mathoperation(int a, int b, int* sum, int* diff)
{
    *sum = a + b;
    *diff = a - b;
}