add_library(detector
    Detector.cpp
)

target_include_directories(detector PUBLIC
    ./
)

target_link_libraries(detector
    common
)