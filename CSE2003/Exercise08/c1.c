#include <stdio.h>

void binary(int*, int*, int*, int*, int*, char);

int main(void)
{
    char letter;
    printf("대문자 하나를 입력하세요: ");
    scanf("%c", &letter);

    int b0, b1, b2, b3, b4;
    binary(&b0, &b1, &b2, &b3, &b4, letter);
    printf("이진수 출력 결과: %d%d%d%d%d\n", b0, b1, b2, b3, b4);

    return 0;
}

void binary(int* b0, int* b1, int* b2, int* b3, int* b4, char c)
{
    // 0  0  0  0  0
    // ^  ^  ^  ^  ^
    // b0 b1 b2 b3 b4

    int value = c - 'A';
    *b4 = value % 2;
    value = value / 2;
    *b3 = value % 2;
    value = value / 2;
    *b2 = value % 2;
    value = value / 2;
    *b1 = value % 2;
    value = value / 2;
    *b0 = value % 2;
    value = value / 2;
}
