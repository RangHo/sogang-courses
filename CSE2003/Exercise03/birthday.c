#include <stdio.h>

int getYear(int);
int getMonth(int);
int getDate(int);

int main(void)
{
    int birthday;
    printf("What is your birthday? (YYYYMMDD): ");
    scanf("%d", &birthday);

    printf("%d-%d-%d\n", getYear(birthday), getMonth(birthday), getDate(birthday));

    return 0;
}

int getYear(int raw) { return raw / 10000; }

int getMonth(int raw) { return (raw % 10000) / 100; }

int getDate(int raw) { return raw % 10000 % 100; }
