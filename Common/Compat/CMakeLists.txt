add_library(c_libraries_compat STATIC)
target_sources(c_libraries_compat PRIVATE
    compat.h
    d3dx8.h
    d3dx8core.h
    d3dx8core.cpp
    d3dx8math.h
    d3dx8math.cpp
    d3dx8tex.h
    dinput_compat.h
    intrin_compat.h
    memory_compat.h
    string_compat.h
    tchar_compat.h
    time_compat.h
    wchar_compat.h
    windows_compat.h
)

### DXVK for non-Windows platforms
FetchContent_Declare(
            dxvk
            URL        https://github.com/doitsujin/dxvk/releases/download/v2.7.1/dxvk-native-2.7.1-steamrt-sniper.tar.gz
        )
FetchContent_MakeAvailable(dxvk)
# Search library in dxvk-native folder
target_link_directories(c_libraries_compat INTERFACE
    ${dxvk_SOURCE_DIR}/lib
)
target_link_libraries(c_libraries_compat PRIVATE dxvk_d3d8)

### GLM as D3DX8 Math replacement
find_package(glm CONFIG REQUIRED)
target_link_libraries(c_libraries_compat PRIVATE glm::glm)

### GLI as D3DX8 Texture replacement
find_package(gli CONFIG REQUIRED)
target_link_libraries(c_libraries_compat PRIVATE gli)

target_include_directories(c_libraries_compat PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" ${dxvk_SOURCE_DIR}/include/dxvk)