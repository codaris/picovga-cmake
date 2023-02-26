add_executable(vga_levelmeter
    src/main.cpp
    img/repro1.cpp
    img/repro2.cpp
    img/repro3.cpp
    snd/test.cpp
)

add_picovga(vga_levelmeter)

# for vga_config.h include
target_include_directories(vga_levelmeter PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_levelmeter)

# Allow stdio to USB
# pico_enable_stdio_usb(vga_levelmeter 1)