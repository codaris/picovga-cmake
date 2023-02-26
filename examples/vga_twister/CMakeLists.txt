add_executable(vga_twister
    img/CobbleStone.cpp 
    img/Fabric.cpp       
    img/Soil.cpp         
    img/Wood.cpp

    src/main.cpp
)

add_picovga(vga_twister)

# for vga_config.h include
target_include_directories(vga_twister PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_twister)

# Allow stdio to USB
# pico_enable_stdio_usb(vga_twister 1)