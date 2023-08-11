cmake_minimum_required(VERSION 3.12)
project(VOL-File)
set(CMAKE_C_STANDARD 11)

# Find Python 3
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
include_directories(./private)

# Add the source files
set(SOURCES private/vol.c private/main.c)

# Add a shared library target
add_library(VOL-File SHARED ${SOURCES})

# Set the library output name
set_target_properties(VOL-File PROPERTIES OUTPUT_NAME "vol")

# Specify the header file directory
target_include_directories(VOL-File PUBLIC .)

# Set the output directory based on the operating system
if(WIN32)
    set(OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/windows")
    # Set the global library output directory for Windows
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}")
elseif(UNIX AND NOT APPLE)
    set(OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/linux")
else()
    message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()

# Set the library output directory for VOL-File
set_target_properties(VOL-File PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
set_target_properties(VOL-File PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

target_link_libraries(VOL-File PRIVATE Python3::Python)

# Add VOLGUI target if needed
add_executable(VOLGUI private/GUI.c)

# Link libraries for VOL-File and VOLGUI
target_link_libraries(VOLGUI PRIVATE Python3::Python -L${OUTPUT_DIRECTORY} -lvol)

# Set the executable output directory (same as the library output directory)
set_target_properties(VOLGUI PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
