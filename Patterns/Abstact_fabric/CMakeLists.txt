cmake_minimum_required(VERSION 3.12)
project(Fabric)

set(FABR_SOURCES
    main.cpp
    
)

set(FABR_HEADERS

    
)


set(FABR_INCLUDE_DIRS "")  
foreach(_headerFile ${FABR_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND FABR_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES FABR_INCLUDE_DIRS)

add_executable(Fabr ${FABR_SOURCES})
target_include_directories(Fabr PRIVATE ${FABR_INCLUDE_DIRS})
