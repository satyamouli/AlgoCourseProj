cmake_minimum_required(VERSION 3.3)
project(AlgoProj)

find_package(Boost 1.60.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES node.cpp wire.cpp circuit.cpp circ_sim.cpp)

add_executable(BoolLogicSim ${SOURCE_FILES})

target_link_libraries(BoolLogicSim ${Boost_LIBRARIES})
