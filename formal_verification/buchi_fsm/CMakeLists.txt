cmake_minimum_required(VERSION 3.16)
project(buchi_fsm)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

#add_definitions(-DDEBUG)
add_executable(buchi ./src/main.cpp
                     ./src/ltl.cpp
                    ./src/BuchiCreator.cpp
                    ./src/fsm.cpp)
