cmake_minimum_required(VERSION 3.12)
project(Builder)



set(Builder_SOURCES
    main.cpp
)
set(Builder_HEADERS
    
)



set(Builder_INCLUDE_DIRS "")  
foreach(_headerFile ${Builder_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND Builder_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES Builder_INCLUDE_DIRS)

add_executable(Builder ${Builder_SOURCES})
target_include_directories(Builder PRIVATE ${Builder_INCLUDE_DIRS})
