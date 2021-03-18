#include <stdio.h>

float det(int*, int*, int*, int*);

int main(void)
{
    int a, b, c, d;

    printf("Enter a 2x2 matrix (a b c d).\n"
           " +-       -+\n"
           " |  a   b  |\n"
           " |         |\n"
           " |  c   d  |\n"
           " +-       -+\n"
           "Enter here: ");
    scanf("%d %d %d %d", &a, &b, &c, &d);

    printf("Matrix:\n"
           " +-             -+\n"
           " | %5d   %5d |\n"
           " |               |\n"
           " | %5d   %5d |\n"
           " +-             -+\n",
        a, b, c, d);

    printf("Inverse Matrix:\n"
           " +-             -+\n"
           " | %5d   %5d |\n"
           " |               | * %f\n"
           " | %5d   %5d |\n"
           " +-             -+\n",
        d, -b, 1 / det(&a, &b, &c, &d), -c, a);
}

float det(int* a, int* b, int* c, int* d) { return ((*a) * (*d) - (*b) * (*c)) * 1.0f; }
