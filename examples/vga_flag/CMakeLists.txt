add_executable(vga_flag
    src/main.cpp
    img/clouds.cpp
    img/flag.cpp
    img/mast.cpp
)

add_picovga(vga_flag)

# for vga_config.h include
target_include_directories(vga_flag PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_flag)

# Allow stdio to USB
# pico_enable_stdio_usb(vga_balloons 1)