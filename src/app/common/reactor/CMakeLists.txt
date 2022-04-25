
add_library(reactor
    Pipe.cpp
    Event.cpp
    Epoll.cpp
    Link.cpp
    Acceptor.cpp
    Timer.cpp
    Thread.cpp
    MsgMemStorage.cpp
    Reactor.cpp
    ReactorManager.cpp
)

target_include_directories(reactor PUBLIC
    .
    types
)

target_link_libraries(reactor
    pthread
    logger
    utils
)