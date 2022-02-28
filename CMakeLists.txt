cmake_minimum_required(VERSION 3.21)
project(space_rover)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE src/rover.h src/command.h src/position.h src/direction.h src/rover_state.h)
add_executable(test test/rover_test.cc ${SOURCE})
add_executable(examples example/rover_example.cc ${SOURCE})