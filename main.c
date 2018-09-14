#include "usb.h"
#include "io.h"
#include "gcn.h"
#include "event.h"
#include "time.h"

#include <stdio.h>
#include <signal.h>

// Flag for main loop
int shouldDie = 0;

// Sets flag to stop looping
void handle_sigint(int sig) {
    printf("Time to die.\n");
    shouldDie = 1;
}

int main(int argc, char* argv[]) {
    // Ensure correct usage
    if(argc != 3) {
        printf("Correct usage: ./gcn-usb [device] [name]\n");
        printf("Example usage: ./gcn-usb /dev/hidraw0 GC\n");
        return 1;
    }

    // Grab a handle to a USB device
    USBDevice* dev = openDevice(argv[1]);
    if(dev == NULL) {
        printf("ERROR: Failed to open device. Check device name and permissions.\n");
        return 1;
    }

    // Grab a handle to an IO device (mouse/keyboard)
    IODevice* io = createIODevice(argv[2]);
    if(io == NULL) {
        printf("ERROR: Failed to create IO device.\n");
        closeDevice(dev);
        return 1;
    }

    // Setup handler to exit loop on SIGINT (Ctrl+C)
    signal(SIGINT, handle_sigint);

    RawState newRaw;
    Controller controller;
    Time* time = createTime();

    // Loop until sigint
    while(!shouldDie) {
        getTime(time);
        readDeviceData(dev, &newRaw, sizeof(newRaw));
        updateController(&controller, &newRaw);
        //handle_state(&controller, io);
        delayUntil(time, 1000 / 60);
    }

    // Cleanup memory
    destroyIODevice(io);
    closeDevice(dev);
    return 0;
}
