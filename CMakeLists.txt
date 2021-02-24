set(projectName "Raytracer")
cmake_minimum_required (VERSION 2.6)
project (${projectName})

option(test "Build all tests." ON) # Makes boolean 'test' available.

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()

if (NOT CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS   "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
					src
					libs/jsoncpp)

add_definitions(-std=c++17)

add_subdirectory(src)
add_subdirectory(libs)

add_executable(${projectName} main.cpp)

target_link_libraries(${projectName} png raytracerCore externalLibs pthread)
if (test)
    enable_testing ()
    add_subdirectory(test)
endif()

set(CONFIGURED_ONCE TRUE CACHE INTERNAL
    "A flag showing that CMake has configured at least once.")