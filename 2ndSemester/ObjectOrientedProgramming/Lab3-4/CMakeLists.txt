project(a3_4_913_Iaguta_Alen_Mihael C)

set(CMAKE_C_STANDARD 11)

include_directories(array demain main repo service testing ui validation)

add_executable(a3_4_913_Iaguta_Alen_Mihael ${PROJECT_SOURCE_DIR}
        domain.c
        domain.h
        repository.c
        repository.h
        service.c
        service.h
        ui.c
        ui.h
        validation.c
        validation.h
        tests.c
        tests.h)
