add_executable(vga_hypno
    src/main.cpp
)

add_picovga(vga_hypno)

# for vga_config.h include
target_include_directories(vga_hypno PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_hypno)

# Allow stdio to USB
# pico_enable_stdio_usb(vga_balloons 1)