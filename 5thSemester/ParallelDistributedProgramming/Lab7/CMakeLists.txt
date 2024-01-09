cmake_minimum_required(VERSION 3.26)
project(Lab7)

set(CMAKE_CXX_STANDARD 17)

# Include MPI
find_package(MPI REQUIRED)
add_executable(Lab7 main.cpp)
# Add libraries for code completion and compiling
target_link_libraries(Lab7 PUBLIC MPI::MPI_CXX)

set(MPI_INCLUDE_PATH "C:/Program Files (x86)/Microsoft SDKs/MPI/Include")
set(MPI_CXX_LIBRARIES "C:/Program Files (x86)/Microsoft SDKs/MPI/Lib/x64/msmpi.lib")

# Include MPI headers
include_directories(${MPI_INCLUDE_PATH})

# Add executable
add_executable(MPI main.cpp)

# Link MPI libraries
target_link_libraries(MPI ${MPI_CXX_LIBRARIES})