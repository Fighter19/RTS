add_executable(g_main)

if (WIN32)
    target_sources(g_main PRIVATE
        WinMain.h
        WinMain.cpp
    )
else()
    target_sources(g_main PRIVATE
        SDL3Main.h
        SDL3Main.cpp
    )

    find_package(SDL3 REQUIRED)
    find_package(SDL3_image REQUIRED)
    target_link_libraries(g_main PUBLIC SDL3::SDL3 SDL3_image::SDL3_image)
endif()

### Target configuration
set_target_properties(g_main PROPERTIES OUTPUT_NAME Generals)
target_link_libraries(g_main PUBLIC g_gameengine g_gameenginedevice)