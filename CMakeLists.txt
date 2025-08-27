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
# If monitor requires vsync, set the vsync pin.
add_compile_definitions(VGA_GPIO_VSYNC=9)

# Add the examples
add_subdirectory(examples)

# --- Host tool build (native) -----------------------------------------------
include(ExternalProject)

# Toggle if you want (optional)
option(BUILD_HOST_TOOLS "Build native host tools into the tools/ directory" ON)

if(BUILD_HOST_TOOLS)
  # Where to drop the compiled host binaries:
  set(HOST_TOOLS_OUT_DIR "${CMAKE_SOURCE_DIR}/tools")

  # Configure and build a separate native CMake project in /host_tools
  ExternalProject_Add(host_tools_proj
    SOURCE_DIR        "${CMAKE_SOURCE_DIR}/tools/src"
    BINARY_DIR        "${CMAKE_BINARY_DIR}/tools"
    CMAKE_ARGS
      -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
      -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=${HOST_TOOLS_OUT_DIR}
      # (Optional) Propagate your host compiler if you like:
      # -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
      # -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    INSTALL_COMMAND   ""      # we copy via RUNTIME_OUTPUT_DIRECTORY instead
    BUILD_ALWAYS      TRUE    # rebuild if any host tool changes
  )

  # Make a nice top-level target so you can do: cmake --build . --target tools
  add_custom_target(tools ALL
    DEPENDS host_tools_proj
    COMMENT "Building native host tools into ${HOST_TOOLS_OUT_DIR}"
  )
endif()
