#include "usb.h"

#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

#include <linux/uinput.h>
#include <linux/hidraw.h>

struct USBDevice {
    int fd;
};

USBDevice* openDevice(char* name) {
    int fd = open(name, O_RDWR | O_NONBLOCK);
    if(fd == -1) return NULL;

    char buffer[256];
    ioctl(fd, HIDIOCGRAWNAME(256), buffer);
    printf("Opening: %s\n", buffer);

    USBDevice* device = malloc(sizeof(USBDevice));
    device->fd = fd;

    return device;
}

void closeDevice(USBDevice* device) {
    close(device->fd);
    free(device);
}

void getDeviceName(USBDevice* device, char* name, int length) {
    ioctl(device->fd, HIDIOCGRAWNAME(length), name);
}

void readDeviceData(USBDevice* device, void* buffer, int length) {
    lseek(device->fd, 0, SEEK_END);
    read(device->fd, buffer, length);
}