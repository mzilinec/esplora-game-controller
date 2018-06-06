cmake_minimum_required(VERSION 3.6)
project(conf_tool)

add_compile_options(-Wall)
set(CMAKE_CXX_STANDARD 11)

include_directories(${ARD_SOURCES_PATH})
set(SOURCE_FILES main.cpp SerialPort.cpp SerialPort.h gen_keymap.h)
add_executable(conf_tool ${SOURCE_FILES})