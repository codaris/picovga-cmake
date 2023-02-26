add_executable(vga_balloons
    src/main.cpp
    img/clouds.cpp
    img/hotair.cpp
    img/blue.cpp
    img/green.cpp
    img/red.cpp
    img/yellow.cpp
)

add_picovga(vga_balloons)

# for vga_config.h include
target_include_directories(vga_balloons PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_balloons)

# Allow stdio to USB
# pico_enable_stdio_usb(vga_balloons 1)