add_executable(vga_sokoban
    src/main.cpp
    src/game.cpp
    src/select.cpp

    src/levels.cpp
    src/levels_rabbit.cpp
    src/levels_peloux.cpp
    src/levels_murase.cpp
    src/levels_martel.cpp
    src/levels_grigor.cpp
    src/levels_haywood.cpp
    src/levels_holland.cpp
    src/levels_skinner.cpp
    src/levels_sladkey.cpp
    src/levels_damgaard.cpp
    src/levels_loma.cpp
    src/levels_domenech.cpp
    src/levels_dzekic.cpp

    img/tiles8.cpp
    img/tiles12.cpp
    img/tiles16.cpp
    img/tiles20.cpp
    img/tiles24.cpp
    img/tiles28.cpp
    img/tiles32.cpp
    snd/yippee.cpp
)

add_picovga(vga_sokoban)

# for vga_config.h include
target_include_directories(vga_sokoban PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_sokoban)

# Allow stdio to USB
pico_enable_stdio_usb(vga_sokoban 1)