add_executable(vga_life
    src/main.cpp
    #img/tiles32.cpp
    img/tiles16.cpp
)

add_picovga(vga_life)

# for vga_config.h include
target_include_directories(vga_life PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_life)

# Allow stdio to USB
pico_enable_stdio_usb(vga_life 1)