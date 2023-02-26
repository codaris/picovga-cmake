add_executable(vga_pixels
    src/main.cpp
)

add_picovga(vga_pixels)

# for vga_config.h include
target_include_directories(vga_pixels PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_pixels)

# Allow stdio to USB
# pico_enable_stdio_usb(vga_pixels 1)