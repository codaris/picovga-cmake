# This is a copy of <PICOVGA_PATH>/picovga_import.cmake

# This can be dropped into an external project to help locate the PicoVGA SDK
# It should be include()ed prior to project()

if (DEFINED ENV{PICOVGA_PATH} AND (NOT PICOVGA_PATH))
    set(PICOVGA_PATH $ENV{PICOVGA_PATH})
    message("Using PICOVGA_PATH from environment ('${PICOVGA_PATH}')")
endif ()

set(PICOVGA_PATH "${PICOVGA_PATH}" CACHE PATH "Path to the PicoVGA Library")

if (NOT PICOVGA_PATH)
    message(FATAL_ERROR "PicoVGA location was not specified. Please set PICOVGA_PATH.")
endif ()

if (NOT EXISTS ${PICOVGA_PATH})
    message(FATAL_ERROR "Directory '${PICOVGA_PATH}' not found")
endif ()

set(PICOVGA_CMAKE_FILE ${PICOVGA_PATH}/picovga.cmake)
if (NOT EXISTS ${PICOVGA_CMAKE_FILE})
    message(FATAL_ERROR "Directory '${PICOVGA_PATH}' does not appear to contain the PicoVGA library")
endif ()

set(PICOVGA_PATH ${PICOVGA_PATH} CACHE PATH "Path to the PicoVGA library" FORCE)

include(${PICOVGA_CMAKE_FILE})
