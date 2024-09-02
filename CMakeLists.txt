cmake_minimum_required(VERSION 3.29)
project(webApp C)

set(CMAKE_C_STANDARD 99)

# Specify the source files for your project
set(SOURCES
        main.c
        server.c
        routes.c
        handlers.c
)

# Add the executable target
add_executable(webApp ${SOURCES})

# Link against Winsock library
target_link_libraries(webApp ws2_32)
