add_library(c_wwstub STATIC)
target_sources(c_wwstub PRIVATE
    wwdebugstub.cpp
    wwallocstub.cpp
)

### Target configuration
set_target_properties(c_wwstub PROPERTIES OUTPUT_NAME WWStub)
target_link_libraries(c_wwstub PUBLIC c_wwlib)
