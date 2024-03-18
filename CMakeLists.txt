cmake_minimum_required(VERSION 3.5)

project(DesignPattern)

add_compile_options(-std=c++14 -g -Wall -fPIC)

set(SRC
    singleton
    prototype
    factory
    builder
    proxy
    adaptor
    bridge
    decorator
    facade
    flyweight
    composite
    template_method
    strategy
    "command"
    responsibility
    state
    observer
    iterator
)

foreach(dir IN ITEMS ${SRC})
    file(GLOB files "${dir}/*.cpp")
    message(STATUS "DIR : ${dir}")

    foreach(file IN ITEMS ${files})
        get_filename_component(filename ${file} NAME)
        get_filename_component(basename ${file} NAME_WE)
        set(exec "${basename}")
        message(STATUS "FILE: ${dir}/${filename}")

        add_executable(${exec} "${dir}/${filename}")
        target_link_libraries(${exec} pthread)
    endforeach(file IN ITEMS ${dir})
    
endforeach(dir IN ITEMS ${SRC})


