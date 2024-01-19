cmake_minimum_required(VERSION 3.26)
project(Lab8)

set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)
add_executable(Lab8 main.cpp)
target_link_libraries(Lab8 PUBLIC MPI::MPI_CXX)

set(MPI_INCLUDE_PATH "C:/Program Files (x86)/Microsoft SDKs/MPI/Include")
set(MPI_CXX_LIBRARIES "C:/Program Files (x86)/Microsoft SDKs/MPI/Lib/x64/msmpi.lib")

# Include MPI headers
include_directories(${MPI_INCLUDE_PATH})

# Add executable
add_executable(MPI main.cpp)

# Link MPI libraries
target_link_libraries(MPI ${MPI_CXX_LIBRARIES})