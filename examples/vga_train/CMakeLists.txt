add_executable(vga_train
    src/main.cpp
    src/levels.cpp
    src/game.cpp

    img/tiles.cpp

    snd/collect.cpp
    snd/crash.cpp
    snd/step.cpp
    snd/success.cpp
)

add_picovga(vga_train)

# for vga_config.h include
target_include_directories(vga_train PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_train)

# Allow stdio to USB
pico_enable_stdio_usb(vga_train 1)
