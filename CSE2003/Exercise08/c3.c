#include <stdio.h>

int elapsetime(int, int);

int main(void)
{
    int past, future;

    printf("Input time in the past (HHMMSS): ");
    scanf("%d", &past);

    printf("Input time in the future (HHMMSS): ");
    scanf("%d", &future);

    int diff = elapsetime(past, future);

    printf("Time elapsed: %06d", diff);

    return 0;
}

int elapsetime(int past, int future)
{
    int past_second = past % 100;
    past = past / 100;
    int past_minute = past % 100;
    past = past / 100;
    int past_hour = past;

    int future_second = future % 100;
    future = future / 100;
    int future_minute = future % 100;
    future = future / 100;
    int future_hour = future;

    int diff_second = future_second - past_second + 60;
    int diff_minute = future_minute - past_minute + 60 - 1;
    int diff_hour = future_hour - past_hour - 1;

    diff_minute = diff_minute + (diff_second / 60);
    diff_second = diff_second % 60;
    diff_hour = diff_hour + (diff_minute / 60);
    diff_minute = diff_minute % 60;

    return diff_hour * 10000 + diff_minute * 100 + diff_second;
}
