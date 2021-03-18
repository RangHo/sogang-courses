#include <stdio.h>

int palindrome(int, int);
int FindDivisor(int);

int main(void)
{
    int input;

    printf("Input: ");
    scanf("%d", &input);

    if (palindrome(input, 1))
        printf("%d is a palindrome number.\n", input);
    else
        printf("%d is not a palindrome number.\n", input);

    return 0;
}

int palindrome(int target, int digit)
{
    printf("Function call: palindrome(%d, %d)\n", target, digit);

    int divisor = FindDivisor(target);
    int left_target = (target / (divisor / digit)) % 10;
    int right_target = target % (digit * 10) / digit;

    if (target / 10 == 0 || target / digit < digit)
        return 1;

    if (left_target == right_target && palindrome(target, digit * 10))
        return 1;
    else
        return 0;
}

int FindDivisor(int target)
{
    int result = 1;

    while (target / result >= 10)
        result *= 10;

    return result;
}
