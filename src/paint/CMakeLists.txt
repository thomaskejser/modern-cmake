add_executable(paint)

target_sources(paint
        PRIVATE
        main.cpp)

find_package(CLI11)
target_link_libraries(paint
        PRIVATE
        plog::plog
        CLI11::CLI11
        demo::renderer
        demo::shapes
)