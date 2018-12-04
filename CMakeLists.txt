cmake_minimum_required(VERSION 3.12)
project(libwebsockets_demo C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(libwebsockets_demo
        main.c
        simple-http.c
        simple-http.h
        websocket.c
        websocket.h)
