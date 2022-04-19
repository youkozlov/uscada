
add_library(reactor
    Pipe.cpp
    Epoll.cpp
    Link.cpp
    Timer.cpp
    Thread.cpp
    MsgMemPool.cpp
    ReactorSimple.cpp
    ReactorManager.cpp
)

target_include_directories(reactor PUBLIC
    .
    types
)

target_link_libraries(reactor
    pthread
)