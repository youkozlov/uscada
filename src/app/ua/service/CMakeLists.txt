add_library(ua_service
    discovery/UaGetEndpoints.cpp
    discovery/UaDiscoveryService.cpp
    session/UaActivateSession.cpp
    session/UaCloseSession.cpp
    session/UaCreateSession.cpp
    session/UaSession.cpp
    session/UaSessionActivated.cpp
    session/UaSessionCreated.cpp
    session/UaSessionInit.cpp
    session/UaSessionService.cpp
    attribute/UaRead.cpp
    attribute/UaAttributeService.cpp
    UaService.cpp
    UaServiceComponent.cpp
)

target_include_directories(ua_service PUBLIC
    .
    discovery
    session
    attribute
)

target_link_libraries(ua_service
    common
)