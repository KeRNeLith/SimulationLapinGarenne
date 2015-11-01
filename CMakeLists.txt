project(CroissancePopulation CXX)
cmake_minimum_required(VERSION 2.8)

set(ENABLE_MULTITHREADS true CACHE BOOL "Build project with multithreading.")
if (ENABLE_MULTITHREADS)
    find_package(Threads REQUIRED)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")
    add_definitions( -DMULTI_THREADING )
endif()

# Customize build options
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG=1")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")
if (CMAKE_COMPILER_IS_GNUCXX OR MINGW OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        add_definitions("-std=c++11")
        add_definitions("-Wall")
        add_definitions("-Wextra")
        add_definitions("-Wno-long-long")
        add_definitions("-pedantic")
        set(CMAKE_CXX_FLAGS_RELEASE "-O2")
elseif(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

# Prepare the target configuration
include_directories(.)
file(GLOB_RECURSE cp_src ./*.cpp)
file(GLOB_RECURSE cp_headers ./*.h)

add_executable(${PROJECT_NAME} ${cp_headers} ${cp_src})
if (ENABLE_MULTITHREADS)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} )
endif()
