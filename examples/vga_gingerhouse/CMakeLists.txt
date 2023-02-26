add_executable(vga_gingerhouse
    img/01.cpp
    img/02.cpp
    img/03.cpp
    img/04.cpp
    img/05.cpp
    img/06.cpp
    img/07.cpp
    img/08.cpp
    img/09.cpp
    img/10.cpp
    img/11.cpp
    img/12.cpp
    img/13.cpp
    img/14.cpp
    img/15.cpp
    img/16.cpp
    img/17.cpp
    img/18.cpp
    img/19.cpp
    img/20.cpp
    img/22.cpp

    src/main.cpp
)

add_picovga(vga_gingerhouse)

# for vga_config.h include
target_include_directories(vga_gingerhouse PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_gingerhouse)

# Allow stdio to USB
pico_enable_stdio_usb(vga_gingerhouse 1)
