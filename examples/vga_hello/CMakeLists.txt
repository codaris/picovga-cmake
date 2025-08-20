add_executable(vga_hello
    src/main.cpp
)

add_picovga(vga_hello)

# pull in common dependencies
#target_link_libraries(vga_hello pico_stdlib)

# for vga_config.h include
target_include_directories(vga_hello PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

pico_enable_stdio_usb(vga_hello 1)

# create map/bin/hex file etc.
pico_add_extra_outputs(vga_hello)

