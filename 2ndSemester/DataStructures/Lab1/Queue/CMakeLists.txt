cmake_minimum_required(VERSION 3.21)
project(Queue)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Queue
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        Queue.cpp
        Queue.h
        ShortTest.cpp
        ShortTest.h)
