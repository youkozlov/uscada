add_subdirectory(ut)

add_library(common_ua
    common/OpcUaBinaryCodec.cpp
    protocols/ConnectionProtocolCodec.cpp
    protocols/ServerConnection.cpp
    protocols/ServerConnectionInit.cpp
    protocols/ServerConnectionConnecting.cpp
    protocols/ServerConnectionEstablished.cpp
    protocols/ServerConnectionReceiveHello.cpp
    protocols/ClientConnection.cpp
    protocols/ClientConnectionInit.cpp
    protocols/ClientConnectionConnecting.cpp
    protocols/ClientConnectionEstablished.cpp
    protocols/ClientConnectionReceiveAck.cpp
)

target_include_directories(common_ua PUBLIC
    common
    common/types
    protocols
    protocols/msg
)

target_link_libraries(common_ua
    logger
    utils
    reactor
)