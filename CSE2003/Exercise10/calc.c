#include <stdio.h>

float Add(float, float);
float Subtract(float, float);
float Multiply(float, float);
float Divide(float, float);

int main(void)
{
    float left, right;
    char operator;

    printf("Input an expression (operator available: +, -, *, /): ");
    scanf("%f %c %f", &left, &operator, & right);

    float result;

    switch (operator) {
    case '+':
        result = Add(left, right);
        break;

    case '-':
        result = Subtract(left, right);
        break;

    case '*':
        result = Multiply(left, right);
        break;

    case '/':
        if (right == 0) {
            printf("Cannot divide by zero.\n");
            return -1;
        }

        result = Divide(left, right);
        break;

    default:
        printf("Invalid operator: %c\n", operator);
        return 1;
    }

    printf("%5.2f %c %5.2f = %5.2f\n", left, operator, right, result);
    return 0;
}

float Add(float left, float right) { return left + right; }

float Subtract(float left, float right) { return left - right; }

float Multiply(float left, float right) { return left * right; }

float Divide(float left, float right) { return left / right; }
