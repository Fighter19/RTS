add_library(c_wwdownload STATIC
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
set_target_properties(c_wwdownload PROPERTIES OUTPUT_NAME WWDownload)
target_link_libraries(c_wwdownload PUBLIC c_wwlib)
target_include_directories(c_wwdownload PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/../")
add_library(Common::WWDownload ALIAS c_wwdownload)

