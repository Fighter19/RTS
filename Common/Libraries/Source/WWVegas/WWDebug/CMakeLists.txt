add_library(c_wwdebug STATIC
    wwdebug.cpp
    wwdebug.h
    wwhack.h
    wwmemlog.cpp
    wwmemlog.h
    wwprofile.cpp
    wwprofile.h
)

### Target configuration
set_target_properties(c_wwdebug PROPERTIES OUTPUT_NAME WWDebug)
target_link_libraries(c_wwdebug PUBLIC c_wwlib_include g_libraries_include)
add_library(Common::WWDebug ALIAS c_wwdebug)