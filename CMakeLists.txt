cmake_minimum_required(VERSION 3.13)
project(HuntTheWumpus)

set(CMAKE_CXX_STANDARD 14)

#add_executable(HuntTheWumpus MapTest.cpp GameTest.cpp catch-main.cpp Wumpus.hpp)
add_executable(HuntTheWumpus Wumpus.hpp main.cpp)