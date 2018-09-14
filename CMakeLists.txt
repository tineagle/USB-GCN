cmake_minimum_required(VERSION 3.0.0)
project(gcn-usb VERSION 0.1.0 LANGUAGES C)

add_executable(gcn-usb main.c usb.c io.c gcn.c event.c time.c)
target_link_libraries(gcn-usb vulkan)
target_link_libraries(gcn-usb glfw)
target_link_libraries(gcn-usb rt)

set_property(TARGET gcn-usb PROPERTY C_STANDARD 11)