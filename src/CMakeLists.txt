set(SOURCE_FILES main.cpp)

add_executable(main ${SOURCE_FILES})
install(TARGETS main DESTINATION ${INSTALL_BIN_DIR})
