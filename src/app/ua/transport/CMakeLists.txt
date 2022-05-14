add_library(ua_transport
    server/UaTcpConnection.cpp
    server/UaTcpConnectionConnected.cpp
    server/UaTcpConnectionInit.cpp
    server/UaTcpConnectionReceiveHello.cpp
    server/UaTcpServer.cpp
    UaTransport.cpp
    UaTransportComponent.cpp
)

target_include_directories(ua_transport PUBLIC
    .
    server
)

target_link_libraries(ua_transport
    common
)