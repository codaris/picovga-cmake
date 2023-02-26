add_executable(vga_matrixrain
    src/main.cpp
)

add_picovga(vga_matrixrain)

# for vga_config.h include
target_include_directories(vga_matrixrain PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_matrixrain)

# Allow stdio to USB
# pico_enable_stdio_usb(vga_matrixrain 1)