add_executable(vga_fifteen
    src/main.cpp
    img/tiles.cpp
    snd/move.cpp
    snd/bump.cpp
    snd/shuffling.cpp
    snd/fanfare.cpp
)

add_picovga(vga_fifteen)

# for vga_config.h include
target_include_directories(vga_fifteen PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_fifteen)

# Allow stdio to USB
pico_enable_stdio_usb(vga_fifteen 1)