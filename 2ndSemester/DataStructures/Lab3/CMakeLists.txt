cmake_minimum_required(VERSION 3.21)
project(Lab3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab3
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        MultiMap.cpp
        MultiMap.h
        MultiMapIterator.cpp
        MultiMapIterator.h
        ShortTest.cpp
        ShortTest.h
        )
