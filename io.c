#include "io.h"

#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#include <linux/uinput.h>

struct IODevice {
    int fd;
};

// Setup flags for passing events
void setupFeatures(int fd) {
    // Enable key event and move/scroll event classes
    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    ioctl(fd, UI_SET_EVBIT, EV_REL);

    // Enable mouse buttons
    ioctl(fd, UI_SET_KEYBIT, BTN_LEFT);
    ioctl(fd, UI_SET_KEYBIT, BTN_RIGHT);
    ioctl(fd, UI_SET_KEYBIT, BTN_MIDDLE);
    ioctl(fd, UI_SET_KEYBIT, BTN_EXTRA);
    ioctl(fd, UI_SET_KEYBIT, BTN_SIDE);
    
    // Enable arrow keys
    ioctl(fd, UI_SET_KEYBIT, KEY_UP);
    ioctl(fd, UI_SET_KEYBIT, KEY_RIGHT);
    ioctl(fd, UI_SET_KEYBIT, KEY_DOWN);
    ioctl(fd, UI_SET_KEYBIT, KEY_LEFT);

    ioctl(fd, UI_SET_KEYBIT, KEY_TAB);
    ioctl(fd, UI_SET_KEYBIT, KEY_ENTER);
    
    // Enable modifiers
    ioctl(fd, UI_SET_KEYBIT, KEY_LEFTCTRL);
    ioctl(fd, UI_SET_KEYBIT, KEY_LEFTSHIFT);
    ioctl(fd, UI_SET_KEYBIT, KEY_LEFTALT);

    // Enable mouse movement
    ioctl(fd, UI_SET_RELBIT, REL_X);
    ioctl(fd, UI_SET_RELBIT, REL_Y);

    // Enable mouse scrolling
    ioctl(fd, UI_SET_RELBIT, REL_WHEEL);
    ioctl(fd, UI_SET_RELBIT, REL_HWHEEL);
}

IODevice* createIODevice(char* name) {
    int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if(fd == -1) return NULL;

    struct uinput_setup setup;
    memset(&setup, 0, sizeof(setup));

    setup.id.bustype = BUS_USB;
    strcpy(setup.name, name);

    setupFeatures(fd);

    ioctl(fd, UI_DEV_SETUP, &setup);
    ioctl(fd, UI_DEV_CREATE);

    IODevice* device = malloc(sizeof(IODevice));
    device->fd = fd;

    return device;
}

void destroyIODevice(IODevice* device) {
    ioctl(device->fd, UI_DEV_DESTROY);
    close(device->fd);
    free(device);
}

void emit(int fd, int type, int code, int value) {
    struct input_event event;
    memset(&event, 0, sizeof(event));

    event.type = type;
    event.code = code;
    event.value = value;

    write(fd, &event, sizeof(event));
}

IO_FUN(sendEvents) {
    emit(device->fd, EV_SYN, SYN_REPORT, 0);
}

#define EMIT_KEY(type) emit(device->fd, EV_KEY, type, state)
#define EMIT_REL(type, value) emit(device->fd, EV_REL, type, value);

// Mouse buttons
IO_STATE_FUN(leftClick) {
    EMIT_KEY(BTN_LEFT);
}

IO_STATE_FUN(rightClick) {
    EMIT_KEY(BTN_RIGHT);
}

IO_STATE_FUN(middleClick) {
    EMIT_KEY(BTN_MIDDLE);
}

IO_STATE_FUN(forwardClick) {
    EMIT_KEY(BTN_EXTRA);
}

IO_STATE_FUN(backClick) {
    EMIT_KEY(BTN_SIDE);
}

// Arrow keys
IO_STATE_FUN(upArrow) {
    EMIT_KEY(KEY_UP);
}

IO_STATE_FUN(rightArrow) {
    EMIT_KEY(KEY_RIGHT);
}

IO_STATE_FUN(downArrow) {
    EMIT_KEY(KEY_DOWN);
}

IO_STATE_FUN(leftArrow) {
    EMIT_KEY(KEY_LEFT);
}

// Modifier keys
IO_STATE_FUN(controlKey) {
    EMIT_KEY(KEY_LEFTCTRL);
}

IO_STATE_FUN(shiftKey) {
    EMIT_KEY(KEY_LEFTSHIFT);
}

IO_STATE_FUN(altKey) {
    EMIT_KEY(KEY_LEFTALT);
}

// Other keys
IO_STATE_FUN(tabKey) {
    EMIT_KEY(KEY_TAB);
}

IO_STATE_FUN(enterKey) {
    EMIT_KEY(KEY_ENTER);
}

// Scrolling
IO_COORD_FUN(mouseMove) {
    EMIT_REL(REL_X, x);
    EMIT_REL(REL_Y, y);
}

IO_COORD_FUN(mouseScroll) {
    EMIT_REL(REL_WHEEL, y);
    EMIT_REL(REL_HWHEEL, x);
}