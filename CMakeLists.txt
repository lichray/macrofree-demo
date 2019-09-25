cmake_minimum_required(VERSION 3.15)
project(macrofree_demo LANGUAGES CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

if(BUILD_SHARED_LIBS)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

if(MSVC)
    add_compile_options($<$<COMPILE_LANGUAGE:CXX>:/W3>)
else()
    add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wall>)
    add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wconversion>)
    add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wsign-conversion>)
    add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wsign-compare>)
endif()

if(MINGW)
    add_definitions(-DMINGW_HAS_SECURE_API)
endif()

add_library(macrofree_demo)

set(macrofree_demo_srcs PUBLIC
    include/macrofree_demo/c_file_funcs.h
    src/c_file_funcs.cc)

target_sources(macrofree_demo ${macrofree_demo_srcs})

set(tests_srcs tests/run.cc)

if(BUILD_TESTING)
    find_package(doctest CONFIG REQUIRED)
    add_executable(run ${tests_srcs})
    target_link_libraries(run macrofree_demo doctest::doctest)
    set_property(TARGET run PROPERTY RUNTIME_OUTPUT_DIRECTORY tests)
    add_test(NAME testall COMMAND run WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif()
