add_library(ua_securechannel
    channel/UaServerSecureChannel.cpp
    channel/UaServerSecureChannelEstablished.cpp
    channel/UaServerSecureChannelInit.cpp
    UaSecureChannel.cpp
    UaSecureChannelComponent.cpp
)

target_include_directories(ua_securechannel PUBLIC
    .
    channel
)

target_link_libraries(ua_securechannel
    common
)