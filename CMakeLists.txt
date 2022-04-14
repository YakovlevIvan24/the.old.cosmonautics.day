cmake_minimum_required(VERSION 3.20)
project(TheOldCD)

set(CMAKE_CXX_STANDARD 20)

add_executable(TheOldCD main.cpp)


set(SFML_STATIC_LIBRARIES true)

set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
include_directories(c:/SFML/include)
target_link_libraries(TheOldCD sfml-window sfml-graphics sfml-audio)