add_library(controller
    ControlLink.cpp
    Controller.cpp
)

target_include_directories(controller PUBLIC
    ./
)

target_link_libraries(controller
    common
)