cmake_minimum_required(VERSION 3.20)
project(FlappyBird)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")

add_executable(FlappyBird ${SOURCES})

target_link_libraries(FlappyBird 
    sfml-graphics 
    sfml-window 
    sfml-system
)