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


### Installer Setuo
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
include(CPack)
cpack_add_component(GENERALS DISPLAY_NAME "C&C Generals"
  DESCRIPTION "Binaries required for playing C&C Generals"
)
cpack_add_component(ZEROHOUR DISPLAY_NAME "C&C Generals - Zero Hour"
  DESCRIPTION "Binaries required for playing C&C Generals - Zero Hour"
)
cpack_add_component(BFME DISPLAY_NAME "Battle for middleearth"
  DESCRIPTION "Binaries required for playing Battle for middleearth"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(Common)
add_subdirectory(Generals)
add_subdirectory(GeneralsMD)