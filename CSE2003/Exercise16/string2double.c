#include <stdio.h>

float string2float(char*);

int main(void)
{
    char str[10];
    scanf("%s", str);

    printf("Result: %4.6f\n", string2float(str));

    return 0;
}

float string2float(char* str)
{
    float result = 0.0f;
    int is_negative = 0;
    int is_decimal = 0;
    int shifts = 0;
    int index = 0;
    char target;

    if (str[0] == '-') {
        is_negative = 1;
        index++;
    }

    while (str[index] != 0) {
        target = str[index];

        if (target >= '0' && target <= '9') {
            result += target - '0';
            result *= 10;

            if (is_decimal)
                shifts++;
        } else if (target == '.') {
            is_decimal = 1;
        }

        index++;
    }

    // Shift the decimal places properly
    for (int i = 0; i <= shifts; i++)
        result /= 10;

    return (is_negative) ? -result : result;
}
