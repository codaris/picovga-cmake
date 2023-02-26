add_executable(vga_raytrace
    src/main.cpp
    src/render.cpp
)

add_picovga(vga_raytrace)

# for vga_config.h include
target_include_directories(vga_raytrace PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_raytrace)

# Allow stdio to USB
# pico_enable_stdio_usb(vga_balloons 1)