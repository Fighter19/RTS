include(GoogleTest)

# Compression Benchmark
add_executable(CompressionBenchmark 
    CompressionBench.cpp
)

find_package(benchmark REQUIRED)
target_link_libraries(CompressionBenchmark
    PRIVATE c_compression benchmark::benchmark benchmark::benchmark_main
)

# Compression Test
add_executable(CompressionTest 
    CompressionTest.cpp
)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(CompressionTest
    PRIVATE c_compression GTest::gtest GTest::gtest_main
)

gtest_discover_tests(CompressionTest)

# Run compression tool
add_test(
    NAME CompressTool_NoArgs
    COMMAND c_compress
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

set(MAP_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/data/Generals/Maps/official/Alpine Assault/Alpine Assault.map"
    "${CMAKE_CURRENT_SOURCE_DIR}/data/Generals/Maps/official/Armored Fury/Armored Fury.map"
)

foreach(MAP_FILE ${MAP_FILES})
    get_filename_component(MAP_NAME ${MAP_FILE} NAME_WE)

    add_test(
        NAME CompressTool_Map_${MAP_NAME}
        COMMAND c_compress -in ${MAP_FILE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endforeach(MAP_FILE ${MAP_FILES})
