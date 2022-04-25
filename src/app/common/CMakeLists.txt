add_subdirectory(reactor)
add_subdirectory(utils)
add_subdirectory(logger)

add_library(common INTERFACE)

target_include_directories(common INTERFACE
    .
    msg/types
    msg
)

target_link_libraries(common INTERFACE
    logger
    reactor
    utils
)