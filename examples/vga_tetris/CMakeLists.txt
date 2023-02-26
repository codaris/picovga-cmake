add_executable(vga_tetris
    src/main.cpp
    img/tiles.cpp
    snd/brick.cpp
    snd/gameover.cpp
    snd/levelup.cpp
    snd/line.cpp
)

add_picovga(vga_tetris)

# for vga_config.h include
target_include_directories(vga_tetris PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_tetris)

# Allow stdio to USB
pico_enable_stdio_usb(vga_tetris 1)
