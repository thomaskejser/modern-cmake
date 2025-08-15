set(_targetName "${PROJECT_NAME}_paint")

find_package(CLI11)

add_executable(${_targetName})

target_sources(${_targetName}
        PRIVATE
        main.cpp)

target_link_libraries(${_targetName}
        PRIVATE
        plog::plog
        CLI11::CLI11
        demo::renderer
        demo::shapes
)