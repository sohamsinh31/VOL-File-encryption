cmake_minimum_required(VERSION 3.12)
project(VOL-File)

# Set the C standard to C11
set(CMAKE_C_STANDARD 11)

include_directories(./private)

# Add the source files
set(SOURCES private/vol.c private/main.c)

# Add a shared library target
add_library(VOL-File SHARED ${SOURCES})
add_executable(VOLGUI private/GUI.c)

# Set the library output name
set_target_properties(VOL-File PROPERTIES OUTPUT_NAME "vol")

# Specify the header file directory
target_include_directories(VOL-File PUBLIC .)

# Set the output directory based on the operating system
if(WIN32)
    set(OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/windows")
elseif(UNIX AND NOT APPLE)
    set(OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/linux")
else()
    message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()

# Set the library output directory
set_target_properties(VOL-File PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
target_link_libraries(VOL-File -lpython3.10)
target_link_libraries(VOLGUI -lpython3.10 -lvol)
