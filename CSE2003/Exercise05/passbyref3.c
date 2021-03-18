#include <stdio.h>

void MoveUp(int*, int*, int);
void MoveDown(int*, int*, int);
void MoveLeft(int*, int*, int);
void MoveRight(int*, int*, int);

int main(void)
{
    int x, y;

    printf("Enter (x, y): ");
    scanf("%d %d", &x, &y);

    MoveUp(&x, &y, 3);
    printf("Current (x, y): (%d, %d)\n", x, y);

    MoveRight(&x, &y, 10);
    printf("Current (x, y): (%d, %d)\n", x, y);

    MoveDown(&x, &y, 8);
    printf("Current (x, y): (%d, %d)\n", x, y);

    MoveLeft(&x, &y, 21);
    printf("Current (x, y): (%d, %d)\n", x, y);

    return 0;
}

void MoveUp(int* x, int* y, int dist)
{
    printf("Moving up by %d...\n", dist);
    *y += dist;
}

void MoveDown(int* x, int* y, int dist)
{
    printf("Moving down by %d...\n", dist);
    *y -= dist;
}

void MoveLeft(int* x, int* y, int dist)
{
    printf("Moving left by %d...\n", dist);
    *x -= dist;
}

void MoveRight(int* x, int* y, int dist)
{
    printf("Moving right by %d...\n", dist);
    *x += dist;
}
