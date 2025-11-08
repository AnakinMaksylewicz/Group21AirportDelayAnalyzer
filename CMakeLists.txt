#file was built with intention to make sfml able to run on any machine, made portable by building statically
cmake_minimum_required(VERSION 3.20)
project(FlightDelayAnalyzer)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

include(FetchContent)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

add_executable(FlightDelayAnalyzer
        src/main.cpp
        src/menu.cpp
        src/heap_sort.cpp
        src/merge_sort.cpp
        src/csv_parser.cpp
        src/data_generator.cpp
        include/compare.h
        src/compare.cpp
        include/quick_sort.h
        src/quick_sort.cpp
        include/sfml_menu.h
        src/sfml_menu.cpp
)

target_link_libraries(FlightDelayAnalyzer
    PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        winmm
        gdi32
        opengl32
)

# was getting an error with running sfml, this fixes it
add_custom_command(
        TARGET FlightDelayAnalyzer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:FlightDelayAnalyzer>/assets"
)
set_target_properties(FlightDelayAnalyzer PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
