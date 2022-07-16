set(TEST_FILES test.cpp)

add_executable(test ${TEST_FILES})

target_link_libraries(test PRIVATE lib)

install(TARGETS test DESTINATION ${INSTALL_BIN_DIR})
