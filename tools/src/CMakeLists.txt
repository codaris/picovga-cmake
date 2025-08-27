cmake_minimum_required(VERSION 3.20)
project(pico_host_tools LANGUAGES C CXX)

# Host build settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# You can add include dirs/libs here if your tools share code:
# include_directories(${CMAKE_SOURCE_DIR}/include)
# find_package(...)

# Gather all one-file utilities in this folder
file(GLOB HOST_TOOL_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

if(NOT HOST_TOOL_SOURCES)
  message(STATUS "No host tool sources found in ${CMAKE_CURRENT_SOURCE_DIR}")
endif()

foreach(src IN LISTS HOST_TOOL_SOURCES)
  get_filename_component(name "${src}" NAME_WE)
  add_executable(${name} "${src}")

  # Let parent control where the binaries go (default to local build dir)
  # Parent passes -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=<repo>/tools
  set_target_properties(${name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
  )

  # Optional: link libraries if needed
  # target_link_libraries(${name} PRIVATE some_lib)
endforeach()