#ifndef USB_H
#define USB_H

typedef struct USBDevice USBDevice;

USBDevice* openDevice(char* name);
void closeDevice(USBDevice* device);

void getDeviceName(USBDevice* device, char* name, int length);
void readDeviceData(USBDevice* device, void* buffer, int length);

#endif