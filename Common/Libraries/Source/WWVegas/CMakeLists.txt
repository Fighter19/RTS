add_library(c_wwlib_include INTERFACE)
target_include_directories(c_wwlib_include INTERFACE "WWLib")

add_library(c_wwdebug_include INTERFACE)
target_include_directories(c_wwdebug_include INTERFACE "WWDebug")

add_library(c_wwmath_include INTERFACE)
target_include_directories(c_wwmath_include INTERFACE "WWMath")

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
add_library(c_wwvegas INTERFACE)
target_link_libraries(c_wwvegas INTERFACE c_wwlib c_wwdebug c_wwmath)
target_include_directories(c_wwvegas INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
if(WIN32)
  target_link_libraries(c_wwvegas INTERFACE c_wwdownload)
endif()
