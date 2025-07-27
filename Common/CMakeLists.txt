set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/common/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/common/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/common/bin)

include(Deps/dx8.cmake)
include(Deps/lzhl.cmake)
include(Deps/gamespy.cmake)

add_subdirectory(Compat)
add_subdirectory(Libraries)