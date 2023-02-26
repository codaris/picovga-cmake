add_executable(vga_oscilloscope
    src/main.cpp
    img/grid.cpp
    img/oscilA.cpp
    img/oscilB1.cpp
    img/oscilB2.cpp
    img/oscilC1.cpp
    img/oscilC2.cpp
    img/oscilD.cpp
)

add_picovga(vga_oscilloscope)

# for vga_config.h include
target_include_directories(vga_oscilloscope PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_oscilloscope)

# Allow stdio to USB
# pico_enable_stdio_usb(vga_oscilloscope 1)