add_library(c_compression STATIC
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
set_target_properties(c_compression PROPERTIES OUTPUT_NAME Compression)
target_link_libraries(c_compression PUBLIC c_libraries_include)
target_include_directories(c_compression PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../)
add_library(Gen::Compression ALIAS c_compression)

### ZLIB Compression
if(RTS_USE_ZLIB)
    find_package(ZLIB REQUIRED)
    if(ZLIB_FOUND)
        target_link_libraries(c_compression PUBLIC ZLIB::ZLIB)
    endif()
    target_compile_definitions(c_compression PUBLIC RTS_USE_ZLIB)
endif()

### LZHL Compression
if(RTS_USE_LZHL)
    target_link_libraries(c_compression PUBLIC liblzhl)
    target_compile_definitions(c_compression PUBLIC RTS_USE_LZHL)
endif()