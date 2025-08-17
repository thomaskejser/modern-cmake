set(_targetName "${PROJECT_NAME}_shapes")

add_library(${_targetName} STATIC)
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
