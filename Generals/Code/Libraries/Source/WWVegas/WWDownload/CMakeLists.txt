add_library(g_wwdownload STATIC
    Download.cpp
    Download.h
    DownloadDebug.h
    downloaddefs.h
    FTP.CPP
    ftp.h
    ftpdefs.h
    registry.cpp
    Registry.h
    urlBuilder.cpp
    urlBuilder.h
)

### Target configurations
set_target_properties(g_wwdownload PROPERTIES OUTPUT_NAME WWDownload)
target_link_libraries(g_wwdownload PUBLIC g_wwlib)
target_include_directories(g_wwdownload PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/../")
add_library(Gen::WWDownload ALIAS g_wwdownload)

