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
option(RTS_USE_GLM "Use GLM for math operations" ON)
add_feature_info(GLM RTS_USE_GLM "Use GLM for math operations")
option(RTS_USE_ZLIB "Use ZLIB for compression" ON)
add_feature_info(ZLIB RTS_USE_ZLIB "Support ZLIB for compression (maps etc.)")
option(RTS_USE_LZHL "Use LZHL for compression" ON)
add_feature_info(LZHL RTS_USE_LZHL "Support LZHL for compression (maps etc.)")
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