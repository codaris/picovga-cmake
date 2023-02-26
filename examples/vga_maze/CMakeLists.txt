add_executable(vga_maze
    src/main.cpp
    img/tiles.cpp
)

add_picovga(vga_maze)

# for vga_config.h include
target_include_directories(vga_maze PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_maze)

# Allow stdio to USB
pico_enable_stdio_usb(vga_maze 1)
