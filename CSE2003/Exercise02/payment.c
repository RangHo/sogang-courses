#include <stdio.h>

int main(void)
{
    int price;

    printf("Price: ");
    scanf("%d", &price);

    int compounded_price = price * 1.05f * 1.05f * 1.05f;

    printf("=============== Output ===============\n");
    printf("Months\t\t:%10d %10d\n", 3, 6);
    printf("Total Payment\t:%10d %10d\n", price, compounded_price);
    printf("--------------------------------------\n");
    printf("Monthly Payment\t:%10.2f %10.2f\n", price / 3.0f, compounded_price / 6.0f);

    return 0;
}
