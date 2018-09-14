#include "time.h"


#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

struct Time {
    struct timespec start;
};

Time* createTime() {
    Time* time = malloc(sizeof(Time));
    return time;
}

void destroyTime(Time* time) {
    free(time);
}

void getTime(Time* time) {
    clock_gettime(CLOCK_REALTIME, &(time->start));
}

void delayUntil(Time* time, long msec) {
    // Get current time for comparison
    struct timespec end;
    clock_gettime(CLOCK_REALTIME, &end);

    // Calculate time difference
    long elapsed = end.tv_nsec - time->start.tv_nsec;
    struct timespec request;
    request.tv_sec = 0;
    request.tv_nsec = (msec * 1000000L) - elapsed;

    // Sleep about the right amount
    struct timespec remaining;
    nanosleep(&request, &remaining);
}