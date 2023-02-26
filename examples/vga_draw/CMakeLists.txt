add_executable(vga_draw
    img/rpi1.cpp
    img/rpi2.cpp
    img/rpi4.cpp
    img/rpi8.cpp
    img/peter1.cpp
    img/peter2.cpp
    img/peter4.cpp
    img/peter8.cpp

    src/main.cpp
)

add_picovga(vga_draw)

# for vga_config.h include
target_include_directories(vga_draw PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_draw)

# Allow stdio to USB
# pico_enable_stdio_usb(vga_draw 1)