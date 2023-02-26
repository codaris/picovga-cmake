add_executable(vga_ghostracing
    img/tiles.cpp
    img/skyline.cpp
    img/car1.cpp
    img/car2.cpp
    img/car3.cpp
    img/ghost1.cpp
    img/ghost2.cpp
    img/ghost3.cpp
    img/ghost4.cpp
    snd/engine.cpp

    src/main.cpp
)

add_picovga(vga_ghostracing)

# for vga_config.h include
target_include_directories(vga_ghostracing PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_ghostracing)

# Allow stdio to USB
pico_enable_stdio_usb(vga_ghostracing 1)
