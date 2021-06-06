cmake_minimum_required(VERSION 3.14)
project(AgarIO)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(SOURCE_FILES main.cpp Game.cpp Game.h Dot.cpp Dot.h Player.cpp Player.h Highscore.cpp Highscore.h Menu.cpp Menu.h Result.cpp Result.h)
add_executable(AgarIO ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(AgarIO sfml-system sfml-window sfml-graphics sfml-audio sfml-network)