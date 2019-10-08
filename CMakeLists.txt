cmake_minimum_required(VERSION 3.15)
project(macrofree_demo LANGUAGES CXX)

include(CTest)
include(CheckSymbolExists)

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
    add_definitions($<$<COMPILE_LANGUAGE:CXX>:-DMINGW_HAS_SECURE_API>)
endif()

add_library(macrofree_demo)

set(macrofree_demo_srcs PUBLIC
    include/macrofree_demo/c_file_funcs.h)

if(MSVC OR MINGW)
    list(APPEND macrofree_demo_srcs src/win32.cc)
else()
    list(APPEND macrofree_demo_srcs src/posix.cc)
endif()

target_sources(macrofree_demo ${macrofree_demo_srcs})
target_include_directories(macrofree_demo PUBLIC
    include
    ${CMAKE_CURRENT_BINARY_DIR}/include)

check_symbol_exists(fopen_s stdio.h HAVE_FOPEN_S)
if(HAVE_FOPEN_S)
    set(HAVE_ANNEX_K true)
else()
    set(HAVE_ANNEX_K false)
endif()

configure_file(
    include/macrofree_demo/build_config.h.in
    include/macrofree_demo/build_config.h @ONLY)

set(tests_srcs
    tests/test_c_file_funcs.cc
    tests/run.cc)

if(BUILD_TESTING)
    find_package(doctest CONFIG REQUIRED)
    add_executable(run ${tests_srcs})
    target_link_libraries(run macrofree_demo doctest::doctest)
    set_property(TARGET run PROPERTY RUNTIME_OUTPUT_DIRECTORY tests)
    add_test(NAME testall COMMAND run WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif()
