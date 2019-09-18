#include <stdio.h>
#include <time.h>

int main() {
    long int secondsSinceEpoch;
    struct tm currentTime, *pTime;
    int hour, minute, secand, day, month, year;

    secondsSinceEpoch = time(0);

    printf("time() - seconds since epoch: %ld\n", secondsSinceEpoch);

    pTime = &currentTime;

    localtime_r(&secondsSinceEpoch, pTime);

    hour = currentTime.tm_hour;
    minute = currentTime.tm_min;
    secand = currentTime.tm_sec;

    printf("Local time: %02d:%02d:%02d\n", hour, minute, secand);
    return 0;
}
