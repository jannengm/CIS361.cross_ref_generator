cmake_minimum_required(VERSION 3.6)
project(Project_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    cross_ref.c llist.h llist.c)

add_executable(Project_2 ${SOURCE_FILES})