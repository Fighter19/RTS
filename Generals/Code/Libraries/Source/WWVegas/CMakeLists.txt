add_library(g_wwlib_include INTERFACE)
target_include_directories(g_wwlib_include INTERFACE "WWLib")

add_library(g_wwdebug_include INTERFACE)
target_include_directories(g_wwdebug_include INTERFACE "WWDebug")

add_library(g_wwmath_include INTERFACE)
target_include_directories(g_wwmath_include INTERFACE "WWMath")

### Subdirectories
add_subdirectory(WWLib)
add_subdirectory(WWDebug)
add_subdirectory(WWSaveLoad)
add_subdirectory(WWMath)
add_subdirectory(WW3D2)
if(WIN32)
  add_subdirectory(WWDownload)
endif()

### Meta target that includes all libraries
add_library(g_wwvegas INTERFACE)
target_link_libraries(g_wwvegas INTERFACE g_wwlib g_wwdebug g_wwmath)
target_include_directories(g_wwvegas INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
if(WIN32)
  target_link_libraries(g_wwvegas INTERFACE g_wwdownload)
endif()
