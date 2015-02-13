file(GLOB_RECURSE SRC
    "*.h"
    "*.hpp"
    "*.c"
    "*.cpp"
)

add_library(raytracerCore ${SRC})