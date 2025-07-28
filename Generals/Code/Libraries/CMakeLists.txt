add_library(g_libraries_include INTERFACE)
target_include_directories(g_libraries_include INTERFACE "Include")
target_link_libraries(g_libraries_include INTERFACE c_libraries_compat)

# EA Libraries
add_subdirectory(Source/EABrowserEngine)
add_subdirectory(Source/EABrowserDispatch)
