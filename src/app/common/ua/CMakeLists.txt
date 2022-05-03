add_subdirectory(ut)

add_library(common_ua
    common/OpcUaSduBuffer.cpp
    common/OpcUaBinaryCodec.cpp
    protocols/connection/ConnectionProtocolCodec.cpp
    protocols/connection/OpcUaConnection.cpp
    protocols/connection/ServerConnection.cpp
    protocols/connection/ServerConnectionInit.cpp
    protocols/connection/ServerConnectionConnecting.cpp
    protocols/connection/ServerConnectionConnected.cpp
    protocols/connection/ServerConnectionReceiveHello.cpp
    protocols/connection/ClientConnection.cpp
    protocols/connection/ClientConnectionInit.cpp
    protocols/connection/ClientConnectionConnecting.cpp
    protocols/connection/ClientConnectionConnected.cpp
    protocols/connection/ClientConnectionReceiveAck.cpp
)

target_include_directories(common_ua PUBLIC
    common
    common/types
    protocols
    protocols/msg
    protocols/connection
)

target_link_libraries(common_ua
    logger
    utils
    reactor
)