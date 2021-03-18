#include <stdio.h>

int main(void)
{
    FILE* input;
    FILE* output;

    input = fopen("input32.txt", "r");
    output = fopen("output32.txt", "w");

    float operand1, operand2, result;
    char operator;

    short verified;

    while (fscanf(input, "%f %c %f = %f\n", &operand1, &operator, & operand2, &result)
        && !feof(input)) {
        switch (operator) {
        case '+':
            if (operand1 + operand2 == result)
                verified = 1;
            else
                verified = 0;
            break;

        case '-':
            if (operand1 - operand2 == result)
                verified = 1;
            else
                verified = 0;
            break;

        case '*':
            if (operand1 * operand2 == result)
                verified = 1;
            else
                verified = 0;
            break;

        case '/':
            if (operand1 / operand2 == result)
                verified = 1;
            else
                verified = 0;
            break;

        case '%':
            if ((int)operand1 % (int)operand2 == result)
                verified = 1;
            else
                verified = 0;
            break;
        }

        fprintf(output, "%.2f %c %.2f = %.2f ", operand1, operator, operand2, result);

        if (verified)
            fprintf(output, "correct\n");
        else
            fprintf(output, "incorrect\n");
    }

    fclose(input);
    fclose(output);

    return 0;
}
