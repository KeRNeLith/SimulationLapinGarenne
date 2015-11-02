project(CroissancePopulation CXX)
cmake_minimum_required(VERSION 2.8.11)

# Find Qt5
find_package(Qt5Widgets) # The QtWidgets module finds its own dependencies (QtCore and QtGui)

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

set(CMAKE_AUTOMOC ON) # Specific to Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB_RECURSE uis ./*.ui)
qt5_wrap_ui(ui_headers ${uis})

file(GLOB_RECURSE res ./*.qrc)
qt5_add_resources(qt_res ${res})

add_executable(${PROJECT_NAME} ${cp_headers} ${ui_headers} ${qt_res} ${cp_src})
if (ENABLE_MULTITHREADS)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} )
endif()
qt5_use_modules(${PROJECT_NAME} Widgets)
