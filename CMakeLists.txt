cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(picovga C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )

add_library(picovga STATIC)

pico_generate_pio_header(picovga ${CMAKE_CURRENT_LIST_DIR}/src/vga.pio)
# pico_generate_pio_header(picovga ${CMAKE_CURRENT_LIST_DIR}/terminal/bus6502.pio)

target_sources(picovga PRIVATE
    src/render/vga_atext.S
    src/render/vga_attrib8.S
    src/render/vga_color.S
    src/render/vga_ctext.S
    src/render/vga_dtext.S
    src/render/vga_fastsprite.S
    src/render/vga_ftext.S
    src/render/vga_graph1.S
    src/render/vga_graph2.S
    src/render/vga_graph4.S
    src/render/vga_graph8.S
    src/render/vga_graph8mat.S
    src/render/vga_graph8persp.S
    src/render/vga_gtext.S
    src/render/vga_level.S
    src/render/vga_levelgrad.S
    src/render/vga_mtext.S
    src/render/vga_oscil.S
    src/render/vga_oscline.S
    src/render/vga_persp.S
    src/render/vga_persp2.S
    src/render/vga_plane2.S
    src/render/vga_progress.S
    src/render/vga_sprite.S
    src/render/vga_tile.S
    src/render/vga_tile2.S
    src/render/vga_tilepersp.S
    src/render/vga_tilepersp15.S
    src/render/vga_tilepersp2.S
    src/render/vga_tilepersp3.S
    src/render/vga_tilepersp4.S
    src/vga_blitkey.S
    src/vga_render.S    

    src/vga.cpp
    src/vga_layer.cpp
    src/vga_pal.cpp
    src/vga_screen.cpp
    src/vga_util.cpp
    src/vga_vmode.cpp
    src/util/canvas.cpp
    src/util/mat2d.cpp
    src/util/overclock.cpp
    src/util/print.cpp
    src/util/rand.cpp
    src/util/pwmsnd.cpp
    src/font/font_bold_8x8.cpp
    src/font/font_bold_8x14.cpp
    src/font/font_bold_8x16.cpp
    src/font/font_boldB_8x14.cpp
    src/font/font_boldB_8x16.cpp
    src/font/font_game_8x8.cpp
    src/font/font_ibm_8x8.cpp
    src/font/font_ibm_8x14.cpp
    src/font/font_ibm_8x16.cpp
    src/font/font_ibmtiny_8x8.cpp
    src/font/font_italic_8x8.cpp
    src/font/font_thin_8x8.cpp
    
    terminal/bus6502.cpp
    terminal/console.cpp
    terminal/main.cpp
    terminal/usbhid.cpp
    terminal/terminal.cpp    
)

target_include_directories(picovga PRIVATE terminal)

target_link_libraries(picovga pico_stdlib hardware_pio hardware_dma pico_multicore hardware_interp hardware_pwm tinyusb_board tinyusb_host)

pico_enable_stdio_usb(picovga 0)
pico_enable_stdio_uart(picovga 0)

pico_add_extra_outputs(picovga)
