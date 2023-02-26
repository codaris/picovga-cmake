add_executable(vga_monoscope
    img/monoscope_256x192.cpp
    img/monoscope_300x240.cpp
    img/monoscope_320x200.cpp
    img/monoscope_320x240.cpp
    img/monoscope_360x288.cpp
    img/monoscope_384x288.cpp
    img/monoscope_424x240.cpp
    img/monoscope_400x300.cpp
    img/monoscope_500x400.cpp
    img/monoscope_512x288.cpp
    img/monoscope_528x400.cpp
    img/monoscope_600x480.cpp
    img/monoscope_640x400.cpp
    img/monoscope_640x480.cpp
    img/monoscope_704x400.cpp
    img/monoscope_720x576.cpp
    img/monoscope_768x576.cpp
    img/monoscope_800x600.cpp
    img/monoscope_848x480.cpp
    img/monoscope_1024x576.cpp
    img/monoscope_1024x768.cpp
    img/monoscope_1064x600.cpp
    img/monoscope_1152x864.cpp
    img/monoscope_1360x768.cpp
    img/monoscope_1280x960.cpp
    img/pi-monoscope.cpp

    src/main.cpp
)

add_picovga(vga_monoscope)

# for vga_config.h include
target_include_directories(vga_monoscope PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_monoscope)

# Allow stdio to USB
pico_enable_stdio_usb(vga_monoscope 1)