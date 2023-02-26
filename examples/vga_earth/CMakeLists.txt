add_executable(vga_earth
    src/main.cpp
    img/earth1.cpp
    img/earth2.cpp
)

add_picovga(vga_earth)

# for vga_config.h include
target_include_directories(vga_earth PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_earth)

# Allow stdio to USB
# pico_enable_stdio_usb(vga_earth 1)