add_definitions( -DGTEST_HAS_PTHREAD=1 )

add_executable(ua_test
    OpcUaBinaryStreamTest.cpp
)

target_link_libraries(ua_test
    gmock
    gmock_main
    gtest
    gtest_main
    common_ua
)

add_test(NAME ua_test
         COMMAND $<TARGET_FILE:ua_test>)
