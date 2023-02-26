add_executable(vga_watersurface
    src/main.cpp
    img/forest.cpp
    img/duck.cpp
    snd/river.cpp
)

add_picovga(vga_watersurface)

# for vga_config.h include
target_include_directories(vga_watersurface PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_watersurface)

# Allow stdio to USB
# pico_enable_stdio_usb(vga_watersurface 1)
