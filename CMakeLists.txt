cmake_minimum_required(VERSION 3.29)
project(webApp C)

set(CMAKE_C_STANDARD 11)

add_executable(webApp main.c
        server.h
        server.c)

# Link against Winsock library
target_link_libraries(webApp ws2_32)
