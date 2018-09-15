#include "usb.h"

#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>

#include <linux/uinput.h>
#include <linux/hidraw.h>

struct USBDevice {
    FILE* file;
    char* name;
};

USBDevice* openDevice(char* name) {
    FILE* file = fopen(name, "r");
    if(file == NULL) return NULL;

    USBDevice* device = malloc(sizeof(USBDevice));
    device->file = file;
    device->name = name;

    return device;
}

void closeDevice(USBDevice* device) {
    fclose(device->file);
    free(device);
}

void reopenDevice(USBDevice* device) {
    freopen(device->name, "r", device->file);
}

void readDeviceData(USBDevice* device, void* buffer, int length) {
    reopenDevice(device);
    fread(buffer, length, 1, device->file);
}