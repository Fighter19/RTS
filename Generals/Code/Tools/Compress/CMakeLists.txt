add_executable(g_compress Compress.cpp)

### Target configuration
set_target_properties(g_compress PROPERTIES OUTPUT_NAME Compress)
target_link_libraries(g_compress PUBLIC g_compression)
install(TARGETS g_compress RUNTIME DESTINATION bin COMPONENT GENERALS)