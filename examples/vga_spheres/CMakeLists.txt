add_executable(vga_spheres
    src/main.cpp
)

add_picovga(vga_spheres)

# for vga_config.h include
target_include_directories(vga_spheres PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_spheres)

# Allow stdio to USB
# pico_enable_stdio_usb(vga_spheres 1)