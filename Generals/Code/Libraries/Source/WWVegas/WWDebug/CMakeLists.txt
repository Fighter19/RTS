add_library(g_wwdebug STATIC
    wwdebug.cpp
    wwdebug.h
    wwhack.h
    wwmemlog.cpp
    wwmemlog.h
    wwprofile.cpp
    wwprofile.h
)

### Target configuration
set_target_properties(g_wwdebug PROPERTIES OUTPUT_NAME WWDebug)
target_link_libraries(g_wwdebug PUBLIC g_wwlib_include g_libraries_include)
add_library(Gen::WWDebug ALIAS g_wwdebug)