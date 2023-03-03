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

set(EXECUTABLE_OUTPUT_PATH "build")

# Since this is the picovga project set to the path to this directory        
set(PICOVGA_PATH ${CMAKE_CURRENT_LIST_DIR})
# Include the picovga.cmake to add the add_picovga() macro 
include(picovga.cmake)
# Our monitor requires vsync so set teh vsync pin
add_compile_definitions(VGA_GPIO_VSYNC=9)

# Add the examples
add_subdirectory(examples)

# Control the text output of the examples
#pico_enable_stdio_usb(picovga 0)
#pico_enable_stdio_uart(picovga 0)
