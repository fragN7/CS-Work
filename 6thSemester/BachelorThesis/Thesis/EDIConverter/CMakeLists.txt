cmake_minimum_required(VERSION 3.15)
project(EDIConverter)

set(CMAKE_CXX_STANDARD 17)

# Let CMake know where MSYS2 packages are installed
set(CMAKE_PREFIX_PATH "C:/msys64/ucrt64")

# Add include path for nlohmann json.hpp
include_directories(include)

# Find LibXml2 and LibXslt
find_package(LibXml2 REQUIRED)
find_package(LibXslt REQUIRED)

include_directories(${LIBXML2_INCLUDE_DIR} ${LIBXSLT_INCLUDE_DIR})
link_directories(${LIBXML2_LIBRARY_DIRS} ${LIBXSLT_LIBRARY_DIRS})

add_executable(edi_converter main.cpp)

target_link_libraries(edi_converter ${LIBXML2_LIBRARIES} ${LIBXSLT_LIBRARIES})
