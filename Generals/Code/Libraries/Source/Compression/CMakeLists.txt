add_library(g_compression STATIC
    Compression.h
    CompressionManager.cpp
    EAC/btreeabout.cpp
    EAC/btreecodex.h
    EAC/btreedecode.cpp
    EAC/btreeencode.cpp
    EAC/codex.h
    EAC/gimex.h
    EAC/huffabout.cpp
    EAC/huffcodex.h
    EAC/huffdecode.cpp
    EAC/huffencode.cpp
    EAC/refabout.cpp
    EAC/refcodex.h
    EAC/refdecode.cpp
    EAC/refencode.cpp
    LZHCompress/NoxCompress.cpp
    LZHCompress/NoxCompress.h
)

### Target configuration
set_target_properties(g_compression PROPERTIES OUTPUT_NAME Compression)
target_link_libraries(g_compression PUBLIC g_libraries_include)
target_include_directories(g_compression PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../)
add_library(Gen::Compression ALIAS g_compression)

### ZLIB Compression
find_package(ZLIB REQUIRED)
if(ZLIB_FOUND)
    target_link_libraries(g_compression PUBLIC ZLIB::ZLIB)
endif()

### LZHL Compression
target_link_libraries(g_compression PUBLIC liblzhl)