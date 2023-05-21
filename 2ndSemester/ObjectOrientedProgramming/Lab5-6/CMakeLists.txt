cmake_minimum_required(VERSION 3.21)
project(a5_6_913_Iaguta_Alen_Mihael)

set(CMAKE_CXX_STANDARD 14)

include_directories(array)
include_directories(domain)
include_directories(repo)
include_directories(service)
include_directories(tests)
include_directories(ui)
include_directories(validation)

add_executable(a5_6_913_Iaguta_Alen_Mihael
        array/Array.h
        domain/domain.cpp
        domain/domain.h
        main/main.cpp
        repo/repository.cpp
        repo/repository.h
        service/service.cpp
        service/service.h
        tests/tests.cpp
        tests/tests.h
        ui/Ui.cpp
        ui/Ui.h
        validation/validation.cpp
        validation/validation.h errors/exceptions.h)
