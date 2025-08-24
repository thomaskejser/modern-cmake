set(_targetName "${PROJECT_NAME}_shapes")

add_library(${_targetName} STATIC)
add_library(demo::shapes ALIAS ${_targetName})

target_sources(${_targetName}
        PUBLIC FILE_SET installed TYPE HEADERS BASE_DIRS include
)
add_subdirectory(include/demo/shapes)

target_sources(${_targetName}
        PRIVATE
        rectangle.cpp
        triangle.cpp
        circle.cpp
        PRIVATE FILE_SET internal TYPE HEADERS FILES
        epsilon.h
)
