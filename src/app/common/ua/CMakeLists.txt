add_subdirectory(ut)

add_library(common_ua
    common/OpcUaBinaryStream.cpp
    common/OpcUaBinaryCodec.cpp
)

target_include_directories(common_ua PUBLIC
    common
    common/types
)

target_link_libraries(common_ua
    logger
)