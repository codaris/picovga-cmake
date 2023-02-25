# This file should be included in your project to use the picovga library
# the PICOVGA_PATH variable should be set to the root of the picovga project directory

# The macro add_picovga adds the picovga path references to the specified project.
# PICOVGA_PATH must be set to the root of the picovga project directory
macro(add_picovga project)
    pico_generate_pio_header(${project} ${PICOVGA_PATH}/src/vga.pio)

    target_sources(${project} PRIVATE
        ${PICOVGA_PATH}/src/render/vga_atext.S
        ${PICOVGA_PATH}/src/render/vga_attrib8.S
        ${PICOVGA_PATH}/src/render/vga_color.S
        ${PICOVGA_PATH}/src/render/vga_ctext.S
        ${PICOVGA_PATH}/src/render/vga_dtext.S
        ${PICOVGA_PATH}/src/render/vga_fastsprite.S
        ${PICOVGA_PATH}/src/render/vga_ftext.S
        ${PICOVGA_PATH}/src/render/vga_graph1.S
        ${PICOVGA_PATH}/src/render/vga_graph2.S
        ${PICOVGA_PATH}/src/render/vga_graph4.S
        ${PICOVGA_PATH}/src/render/vga_graph8.S
        ${PICOVGA_PATH}/src/render/vga_graph8mat.S
        ${PICOVGA_PATH}/src/render/vga_graph8persp.S
        ${PICOVGA_PATH}/src/render/vga_gtext.S
        ${PICOVGA_PATH}/src/render/vga_level.S
        ${PICOVGA_PATH}/src/render/vga_levelgrad.S
        ${PICOVGA_PATH}/src/render/vga_mtext.S
        ${PICOVGA_PATH}/src/render/vga_oscil.S
        ${PICOVGA_PATH}/src/render/vga_oscline.S
        ${PICOVGA_PATH}/src/render/vga_persp.S
        ${PICOVGA_PATH}/src/render/vga_persp2.S
        ${PICOVGA_PATH}/src/render/vga_plane2.S
        ${PICOVGA_PATH}/src/render/vga_progress.S
        ${PICOVGA_PATH}/src/render/vga_sprite.S
        ${PICOVGA_PATH}/src/render/vga_tile.S
        ${PICOVGA_PATH}/src/render/vga_tile2.S
        ${PICOVGA_PATH}/src/render/vga_tilepersp.S
        ${PICOVGA_PATH}/src/render/vga_tilepersp15.S
        ${PICOVGA_PATH}/src/render/vga_tilepersp2.S
        ${PICOVGA_PATH}/src/render/vga_tilepersp3.S
        ${PICOVGA_PATH}/src/render/vga_tilepersp4.S
        ${PICOVGA_PATH}/src/vga_blitkey.S
        ${PICOVGA_PATH}/src/vga_render.S    

        ${PICOVGA_PATH}/src/vga.cpp
        ${PICOVGA_PATH}/src/vga_layer.cpp
        ${PICOVGA_PATH}/src/vga_pal.cpp
        ${PICOVGA_PATH}/src/vga_screen.cpp
        ${PICOVGA_PATH}/src/vga_util.cpp
        ${PICOVGA_PATH}/src/vga_vmode.cpp
        ${PICOVGA_PATH}/src/util/canvas.cpp
        ${PICOVGA_PATH}/src/util/mat2d.cpp
        ${PICOVGA_PATH}/src/util/overclock.cpp
        ${PICOVGA_PATH}/src/util/print.cpp
        ${PICOVGA_PATH}/src/util/rand.cpp
        ${PICOVGA_PATH}/src/util/pwmsnd.cpp
        ${PICOVGA_PATH}/src/font/font_bold_8x8.cpp
        ${PICOVGA_PATH}/src/font/font_bold_8x14.cpp
        ${PICOVGA_PATH}/src/font/font_bold_8x16.cpp
        ${PICOVGA_PATH}/src/font/font_boldB_8x14.cpp
        ${PICOVGA_PATH}/src/font/font_boldB_8x16.cpp
        ${PICOVGA_PATH}/src/font/font_game_8x8.cpp
        ${PICOVGA_PATH}/src/font/font_ibm_8x8.cpp
        ${PICOVGA_PATH}/src/font/font_ibm_8x14.cpp
        ${PICOVGA_PATH}/src/font/font_ibm_8x16.cpp
        ${PICOVGA_PATH}/src/font/font_ibmtiny_8x8.cpp
        ${PICOVGA_PATH}/src/font/font_italic_8x8.cpp
        ${PICOVGA_PATH}/src/font/font_thin_8x8.cpp
    )

    target_link_libraries(${project} pico_stdlib hardware_pio hardware_dma pico_multicore hardware_interp hardware_pwm)

    include_directories(${project} ${CMAKE_CURRENT_BINARY_DIR})
endmacro()
