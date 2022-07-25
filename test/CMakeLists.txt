set(TEST_FILES test.cpp GameLoop_test.cpp GameLoop_test.h)

add_executable(test ${TEST_FILES})

target_link_libraries(test PRIVATE lib)

add_subdirectory(rendering)

install(TARGETS test DESTINATION ${INSTALL_BIN_DIR})
