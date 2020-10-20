project(8080-emu C CXX)
set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 2.8.12)

set(APP_NAME 8080-emulator)
include_directories(src)
set(SOURCES
    src/main.cpp
    src/State.cpp
)

add_executable(${APP_NAME} ${SOURCES})
