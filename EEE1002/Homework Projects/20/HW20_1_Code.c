#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct time_struct {
    int hour;
    int minute;
    int second;
};

int main()
{

    time_t now;
    time(&now);

    struct tm* local = localtime(&now);

    struct time_struct current;
    current.hour = local->tm_hour;
    current.minute = local->tm_min;
    current.second = local->tm_sec;

    printf("\n%d:%d:%d\n", current.hour, current.minute, current.second);

    return 0;
}
