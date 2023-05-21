cmake_minimum_required(VERSION 3.21)
project(Lab5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab5
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SortedSet.cpp
        SortedSet.h
        SortedSetIterator.cpp
        SortedSetIterator.h)
