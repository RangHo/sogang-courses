#include <stdio.h>
#include <stdlib.h>

#define PERIOD 10
#define PRINCIPAL 5000.00

int main()
{
    int year = 0;
    float amount, value;
    float inrate = 0.11;

    amount = PRINCIPAL;

    while (year <= PERIOD) {
        printf("%2d %8.2f\n", year, amount);
        value = amount + inrate * amount;
        year++;

        amount = value;
    }

    system("pause");
    return 0;
}