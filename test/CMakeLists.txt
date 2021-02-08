file(GLOB_RECURSE TESTS_SRC
    "./*.cpp"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gtest)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

add_definitions(-std=c++17)
add_definitions(-O0 -g)
add_subdirectory(gtest)

add_executable(Test  main.cpp ${TESTS_SRC} ${SRC})
target_link_libraries (Test -pthread gtest raytracerCore)