cmake_minimum_required(VERSION 3.21)
project(a8_9_913_Iaguta_Alen_Mihael)

set(CMAKE_CXX_STANDARD 14)

include_directories(array)
include_directories(domain)
include_directories(errors)
include_directories(main)
include_directories(repo)
include_directories(service)
include_directories(tests)
include_directories(ui)
include_directories(validation)

add_executable(a8_9_913_Iaguta_Alen_Mihael
        array/Array.h
        domain/domain.cpp
        domain/domain.h
        errors/exceptions.h
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
        validation/validation.h comparator.cpp comparator.h)
