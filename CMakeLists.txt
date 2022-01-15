cmake_minimum_required(VERSION 3.21)
project(space_rover)

set(CMAKE_CXX_STANDARD 20)

#add_executable(main src/rover.h src/command.h src/position.h src/direction.h src/rover_state.h)
add_executable(test test/rover_test.cc src/rover.h src/command.h src/position.h src/direction.h)
add_executable(examples test/rover_example.cc src/rover.h src/command.h src/position.h src/direction.h)