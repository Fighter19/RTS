add_library(c_benchmark STATIC
    benchmark.h
    benchmark.c
)

### Target configuration
set_target_properties(c_benchmark PROPERTIES OUTPUT_NAME Benchmark)
target_include_directories(c_benchmark PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_library(Common::Benchmark ALIAS c_benchmark)
