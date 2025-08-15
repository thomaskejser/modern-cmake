set(_targetName demo_shapes)

add_library(${_targetName} STATIC
        include/demo/shapes/circle.h
        circle.cpp
        include/demo/shapes/point.h
        ../renderer/svg.cpp
        ../renderer/include/demo/renderer/svg.h
        ../renderer/utility.h)
add_library(demo::shapes ALIAS ${_targetName})

target_sources(${_targetName}
        PUBLIC FILE_SET installed TYPE HEADERS BASE_DIRS include
)
target_sources(${_targetName}
        PRIVATE
        rectangle.cpp
        triangle.cpp
        circle.cpp
)

add_subdirectory(include/demo/shapes)
