add_executable(vga_eggs
    src/main.cpp
    snd/fanfare.cpp
    snd/mapple.cpp
    snd/beep.cpp
    snd/beep2.cpp
    img/computer.cpp
    img/frame.cpp
    img/open.cpp
    img/select.cpp
    img/tiles.cpp
)

add_picovga(vga_eggs)

# for vga_config.h include
target_include_directories(vga_eggs PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_eggs)

# Allow stdio to USB
pico_enable_stdio_usb(vga_eggs 1)