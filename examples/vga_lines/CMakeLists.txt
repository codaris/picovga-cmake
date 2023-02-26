add_executable(vga_lines
    src/main.cpp
)

add_picovga(vga_lines)

# for vga_config.h include
target_include_directories(vga_lines PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_lines)

# Allow stdio to USB
# pico_enable_stdio_usb(vga_lines 1)