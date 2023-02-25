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

set(PICOVGA_PATH ${CMAKE_CURRENT_LIST_DIR}/src)

macro(add_picovga project)
    pico_generate_pio_header(${project} ${PICOVGA_PATH}/vga.pio)

    target_sources(${project} PRIVATE
        ${PICOVGA_PATH}/render/vga_atext.S
        ${PICOVGA_PATH}/render/vga_attrib8.S
        ${PICOVGA_PATH}/render/vga_color.S
        ${PICOVGA_PATH}/render/vga_ctext.S
        ${PICOVGA_PATH}/render/vga_dtext.S
        ${PICOVGA_PATH}/render/vga_fastsprite.S
        ${PICOVGA_PATH}/render/vga_ftext.S
        ${PICOVGA_PATH}/render/vga_graph1.S
        ${PICOVGA_PATH}/render/vga_graph2.S
        ${PICOVGA_PATH}/render/vga_graph4.S
        ${PICOVGA_PATH}/render/vga_graph8.S
        ${PICOVGA_PATH}/render/vga_graph8mat.S
        ${PICOVGA_PATH}/render/vga_graph8persp.S
        ${PICOVGA_PATH}/render/vga_gtext.S
        ${PICOVGA_PATH}/render/vga_level.S
        ${PICOVGA_PATH}/render/vga_levelgrad.S
        ${PICOVGA_PATH}/render/vga_mtext.S
        ${PICOVGA_PATH}/render/vga_oscil.S
        ${PICOVGA_PATH}/render/vga_oscline.S
        ${PICOVGA_PATH}/render/vga_persp.S
        ${PICOVGA_PATH}/render/vga_persp2.S
        ${PICOVGA_PATH}/render/vga_plane2.S
        ${PICOVGA_PATH}/render/vga_progress.S
        ${PICOVGA_PATH}/render/vga_sprite.S
        ${PICOVGA_PATH}/render/vga_tile.S
        ${PICOVGA_PATH}/render/vga_tile2.S
        ${PICOVGA_PATH}/render/vga_tilepersp.S
        ${PICOVGA_PATH}/render/vga_tilepersp15.S
        ${PICOVGA_PATH}/render/vga_tilepersp2.S
        ${PICOVGA_PATH}/render/vga_tilepersp3.S
        ${PICOVGA_PATH}/render/vga_tilepersp4.S
        ${PICOVGA_PATH}/vga_blitkey.S
        ${PICOVGA_PATH}/vga_render.S    

        ${PICOVGA_PATH}/vga.cpp
        ${PICOVGA_PATH}/vga_layer.cpp
        ${PICOVGA_PATH}/vga_pal.cpp
        ${PICOVGA_PATH}/vga_screen.cpp
        ${PICOVGA_PATH}/vga_util.cpp
        ${PICOVGA_PATH}/vga_vmode.cpp
        ${PICOVGA_PATH}/util/canvas.cpp
        ${PICOVGA_PATH}/util/mat2d.cpp
        ${PICOVGA_PATH}/util/overclock.cpp
        ${PICOVGA_PATH}/util/print.cpp
        ${PICOVGA_PATH}/util/rand.cpp
        ${PICOVGA_PATH}/util/pwmsnd.cpp
        ${PICOVGA_PATH}/font/font_bold_8x8.cpp
        ${PICOVGA_PATH}/font/font_bold_8x14.cpp
        ${PICOVGA_PATH}/font/font_bold_8x16.cpp
        ${PICOVGA_PATH}/font/font_boldB_8x14.cpp
        ${PICOVGA_PATH}/font/font_boldB_8x16.cpp
        ${PICOVGA_PATH}/font/font_game_8x8.cpp
        ${PICOVGA_PATH}/font/font_ibm_8x8.cpp
        ${PICOVGA_PATH}/font/font_ibm_8x14.cpp
        ${PICOVGA_PATH}/font/font_ibm_8x16.cpp
        ${PICOVGA_PATH}/font/font_ibmtiny_8x8.cpp
        ${PICOVGA_PATH}/font/font_italic_8x8.cpp
        ${PICOVGA_PATH}/font/font_thin_8x8.cpp
    )

    target_link_libraries(${project} pico_stdlib hardware_pio hardware_dma pico_multicore hardware_interp hardware_pwm)

    include_directories(${project} ${CMAKE_CURRENT_BINARY_DIR})
endmacro()

add_subdirectory(examples)

#pico_enable_stdio_usb(picovga 0)
#pico_enable_stdio_uart(picovga 0)

#pico_add_extra_outputs(picovga)
