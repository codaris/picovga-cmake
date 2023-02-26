add_executable(vga_spots
    src/main.cpp
)

add_picovga(vga_spots)

# for vga_config.h include
target_include_directories(vga_spots PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_spots)

# Allow stdio to USB
# pico_enable_stdio_usb(vga_spots 1)