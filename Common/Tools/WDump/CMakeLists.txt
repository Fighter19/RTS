add_executable(c_wdump)

target_sources(c_wdump PRIVATE
    chunk_d.cpp
    wdump.cpp
    wdumpdoc.cpp
)

### Target configuration
set_target_properties(c_wdump PROPERTIES OUTPUT_NAME WDump)
target_link_libraries(c_wdump PUBLIC c_wwvegas c_wwstub)
install(TARGETS c_wdump RUNTIME DESTINATION bin COMPONENT COMMON)

find_package(SDL3 REQUIRED)
target_link_libraries(c_wdump PUBLIC SDL3::SDL3)

find_package(imgui REQUIRED)
target_link_libraries(c_wdump PUBLIC imgui::imgui)