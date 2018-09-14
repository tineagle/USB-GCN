#ifndef IO_H
#define IO_H

typedef struct IODevice IODevice;

IODevice* createIODevice(char* name);
void destroyIODevice(IODevice* device);

void sendEvents(IODevice* device);

#define IO_FUN(fun) void fun(IODevice* device)
#define IO_STATE_FUN(fun) void fun(IODevice* device, int state)
#define IO_COORD_FUN(fun) void(fun(IODevice* device, int x, int y))

IO_FUN(sendEvents);

IO_STATE_FUN(leftClick);
IO_STATE_FUN(rightClick);
IO_STATE_FUN(middleClick);
IO_STATE_FUN(forwardClick);
IO_STATE_FUN(backClick);

IO_STATE_FUN(upArrow);
IO_STATE_FUN(rightArrow);
IO_STATE_FUN(downArrow);
IO_STATE_FUN(leftArrow);

IO_STATE_FUN(enterKey);
IO_STATE_FUN(tabKey);

IO_STATE_FUN(controlKey);
IO_STATE_FUN(shiftKey);
IO_STATE_FUN(altKey);

IO_COORD_FUN(mouseMove);
IO_COORD_FUN(mouseScroll);

#endif