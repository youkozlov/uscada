add_library(connector
    ConnectorSimple.cpp
)

target_include_directories(connector PUBLIC
    ./
)

target_link_libraries(connector
    common
)