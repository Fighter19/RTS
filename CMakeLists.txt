cmake_minimum_required(VERSION 3.25)
project(RTS LANGUAGES C CXX VERSION 0.1.0)

### Flags
if(UNIX)
    if (APPLE)
        add_compile_definitions(-D_MACOSX)
    else()
        add_compile_definitions(-D_LINUX)
    endif()
    add_compile_definitions(-D_UNIX)
else()
    add_compile_definitions(-D_WINDOWS -DWINVER=0x400 -D_WIN32_WINNT=0x0400 -D_CRT_NONSTDC_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS)
endif()

# Set the different special compilation flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBUG "${CMAKE_CXX_FLAGS_RELWITHDEBUG} -D_INTERNAL")

### Installer Setup
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
include(CPack)
cpack_add_component(COMMON DISPLAY_NAME "Common"
  DESCRIPTION "Binaries required for any game"
)
cpack_add_component(GENERALS DISPLAY_NAME "C&C Generals"
  DESCRIPTION "Binaries required for playing C&C Generals"
)
cpack_add_component(ZEROHOUR DISPLAY_NAME "C&C Generals - Zero Hour"
  DESCRIPTION "Binaries required for playing C&C Generals - Zero Hour"
)
cpack_add_component(BFME DISPLAY_NAME "Battle for middleearth"
  DESCRIPTION "Binaries required for playing Battle for middleearth"
)

# RTS options
include(FeatureSummary)

### Library Options
option(RTS_USE_GLM "Use GLM for math operations" ON)
add_feature_info(GLM RTS_USE_GLM "Use GLM for math operations")
option(RTS_USE_STDFS "Use standard filesystem for file operations" ON)
add_feature_info(STDFS RTS_USE_STDFS "Use standard filesystem for file operations")
option(RTS_USE_FREETYPE "Use FreeType for font rendering" ON)
add_feature_info(FREETYPE RTS_USE_FREETYPE "Use FreeType for font rendering")
option(RTS_USE_FONTCONFIG "Use FontConfig for font discovery" ON)
add_feature_info(FONTCONFIG RTS_USE_FONTCONFIG "Use FontConfig for font discovery")

# Media libraries
option(RTS_USE_BINK "Use BINK for video playback" OFF)
add_feature_info(BINK RTS_USE_BINK "Support BINK for video playback")
option(RTS_USE_MILES "Use Miles Sound System for audio playback" ON)
add_feature_info(MILES RTS_USE_MILES "Support Miles Sound System for audio playback")
option(RTS_USE_OPENAL "Use OpenAL for audio playback" ON)
add_feature_info(OPENAL RTS_USE_OPENAL "Support OpenAL for audio playback")
option(RTS_USE_FFMPEG "Use FFmpeg for video playback" ON)
add_feature_info(FFMPEG RTS_USE_FFMPEG "Support FFmpeg for video playback") 

# Platform-specific librariesq
option(RTS_USE_DX8 "Use DirectX 8 for rendering (Windows only)" ON)
add_feature_info(DX8 RTS_USE_DX8 "Use DirectX 8 for rendering (Windows only)")
option(RTS_USE_SDL3 "Use SDL3 for windowing and input (cross-platform)" ON)
add_feature_info(SDL3 RTS_USE_SDL3 "Use SDL3 for windowing and input (cross-platform)")

# Compression libraries
option(RTS_USE_ZLIB "Use ZLIB for compression" ON)
add_feature_info(ZLIB RTS_USE_ZLIB "Support ZLIB for compression (maps etc.)")
option(RTS_USE_LZHL "Use LZHL for compression" ON)
add_feature_info(LZHL RTS_USE_LZHL "Support LZHL for compression (maps etc.)")

### Build Options
option(RTS_ENABLE_TESTS "Enable tests" OFF)
add_feature_info(TESTS RTS_ENABLE_TESTS "Enable tests & benchmarks")
option(RTS_ENABLE_COVERAGE "Enable code coverage" OFF)
add_feature_info(COVERAGE RTS_ENABLE_COVERAGE "Enable code coverage")
option(RTS_ENABLE_ASAN "Enable AddressSanitizer" OFF)
add_feature_info(ASAN RTS_ENABLE_ASAN "Enable AddressSanitizer")
option(RTS_ENABLE_UBSAN "Enable UndefinedBehaviorSanitizer" OFF)
feature_summary(WHAT ALL)

if(RTS_ENABLE_ASAN)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fsanitize=address")
endif()

if(RTS_ENABLE_UBSAN)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=undefined")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fsanitize=undefined")
endif()

if(RTS_ENABLE_TESTS)
    enable_testing()
endif()

# Add -Werror=nonportable-include-path for GCC and Clang
if(APPLE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=nonportable-include-path")
endif()

if(RTS_ENABLE_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(Common)
add_subdirectory(Generals)
add_subdirectory(GeneralsMD)