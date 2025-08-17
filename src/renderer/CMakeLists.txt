set(_targetName "${PROJECT_NAME}_renderer")

add_library(${_targetName})
add_library(demo::renderer ALIAS ${_targetName})

target_sources(${_targetName}
        PUBLIC FILE_SET installed TYPE HEADERS BASE_DIRS include
)
target_sources(${_targetName}
        PRIVATE
        svg.cpp
        PRIVATE FILE_SET internal TYPE HEADERS FILES
        # internal header used only by this library
        utility.h
)
target_link_libraries(${_targetName}
        PRIVATE
        demo::shapes
)

add_subdirectory(include/demo/renderer)