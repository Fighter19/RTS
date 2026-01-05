add_library(c_wwsaveload STATIC
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
set_target_properties(c_wwsaveload PROPERTIES OUTPUT_NAME WWSaveLoad)
target_link_libraries(c_wwsaveload PUBLIC c_wwlib c_wwmath_include g_libraries_include)
target_include_directories(c_wwsaveload PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
add_library(Common::WWSaveLoad ALIAS c_wwsaveload)
