cmake_minimum_required(VERSION 3.0.0)
project(usb-gcn VERSION 0.1.0 LANGUAGES C)

add_executable(usb-gcn main.c usb.c io.c gcn.c event.c time.c)
target_link_libraries(usb-gcn rt)

set_property(TARGET usb-gcn PROPERTY C_STANDARD 11)