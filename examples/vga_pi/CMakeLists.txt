add_executable(vga_pi
    src/main.cpp
)

add_picovga(vga_pi)

# for vga_config.h include
target_include_directories(vga_pi PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_pi)

# Allow stdio to USB
# pico_enable_stdio_usb(vga_pi 1)