add_executable(c_compress Compress.cpp)

### Target configuration
set_target_properties(c_compress PROPERTIES OUTPUT_NAME Compress)
target_link_libraries(c_compress PUBLIC c_compression)
install(TARGETS c_compress RUNTIME DESTINATION bin COMPONENT COMMON)