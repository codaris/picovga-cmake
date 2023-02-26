add_executable(vga_ants
    src/main.cpp
    src/game.cpp
    img/background.cpp
    img/blacksreds.cpp
    img/cards.cpp
    img/castle.cpp
    img/castle_shadow.cpp
    img/cloud.cpp
    img/cursor.cpp
    img/fence.cpp
    img/fence_shadow.cpp
    img/flags.cpp
    img/grass.cpp
    img/open.cpp
    img/open_sel.cpp
    img/open_sel2.cpp
    img/select.cpp
    img/state.cpp
    img/title.cpp
    img/title2.cpp
    img/trumpet.cpp
    img/win.cpp
    snd/applause.cpp
    snd/birds.cpp
    snd/build_castle.cpp
    snd/build_fence.cpp
    snd/card.cpp
    snd/curse.cpp
    snd/decrease_stocks.cpp
    snd/fanfares.cpp
    snd/increase_power.cpp
    snd/increase_stocks.cpp
    snd/ruin_castle.cpp
    snd/ruin_fence.cpp
)

add_picovga(vga_ants)

# for vga_config.h include
target_include_directories(vga_ants PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_ants)

# Allow stdio to USB
pico_enable_stdio_usb(vga_ants 1)