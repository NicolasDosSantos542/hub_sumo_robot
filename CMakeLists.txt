cmake_minimum_required(VERSION 3.19)
project(hub_sumo_robot)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(test1)

add_executable(hub_sumo_robot
        test1/test1.ino)
