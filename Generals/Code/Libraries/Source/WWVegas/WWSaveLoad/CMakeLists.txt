add_library(g_wwsaveload STATIC
    definition.cpp
    definition.h
    definitionclassids.h
    definitionfactory.cpp
    definitionfactory.h
    definitionfactorymgr.cpp
    definitionfactorymgr.h
    definitionmgr.cpp
    definitionmgr.h
    editable.h
    parameter.cpp
    parameter.h
    parameterlist.h
    parametertypes.h
    persist.h
    persistfactory.cpp
    persistfactory.h
    pointerremap.cpp
    pointerremap.h
    postloadable.h
    saveload.cpp
    saveload.h
    saveloadids.h
    saveloadstatus.cpp
    saveloadstatus.h
    saveloadstatus.h
    saveloadsubsystem.cpp
    saveloadsubsystem.h
    simpledefinitionfactory.h
    simpleparameter.h
    twiddler.cpp
    twiddler.h
    wwsaveload.cpp
    wwsaveload.h
)

### Target configurations
set_target_properties(g_wwsaveload PROPERTIES OUTPUT_NAME WWSaveLoad)
target_link_libraries(g_wwsaveload PUBLIC g_wwlib g_wwmath_include g_libraries_include)
target_include_directories(g_wwsaveload PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
add_library(Gen::WWSaveLoad ALIAS g_wwsaveload)
