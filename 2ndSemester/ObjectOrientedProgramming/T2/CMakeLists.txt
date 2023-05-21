cmake_minimum_required(VERSION 3.21)
project(t2_913_Iaguta_Alen_Mihael_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(t2_913_Iaguta_Alen_Mihael_1
        main.cpp
        service.cpp service.h ui.cpp ui.h dwelling.cpp dwelling.h client.cpp client.h person.cpp person.h company.cpp company.h)
