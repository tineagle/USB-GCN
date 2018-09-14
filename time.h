#ifndef TIME_H
#define TIME_H

typedef struct Time Time;

Time* createTime();
void destroyTime(Time* time);

void getTime(Time* time);
void delayUntil(Time* time, long nsec);

#endif