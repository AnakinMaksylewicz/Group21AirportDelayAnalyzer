cmake_minimum_required(VERSION 3.20)
project(FlightDelayAnalyzer)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

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
        include/data_aggregator.h
        src/data_aggregator.cpp)
