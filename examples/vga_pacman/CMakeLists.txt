add_executable(vga_pacman
    src/data.cpp
    src/game.cpp
    src/main.cpp
    src/open.cpp

    img/logo.cpp
    img/tiles.cpp
    img/sprites.cpp
    img/status.cpp

    snd/startsnd.cpp
    snd/siren.cpp
    snd/wakka.cpp
    snd/frighten.cpp
    snd/eatghost.cpp
    snd/eatfruit.cpp
    snd/death.cpp
    snd/extrapac.cpp
    snd/intermission.cpp
)

add_picovga(vga_pacman)

# for vga_config.h include
target_include_directories(vga_pacman PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_pacman)

# Allow stdio to USB
pico_enable_stdio_usb(vga_pacman 1)
