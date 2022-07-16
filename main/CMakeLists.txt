set(SOURCE_FILES main.cpp)

add_executable(main ${SOURCE_FILES})

target_link_libraries(main PRIVATE lib)

install(TARGETS main DESTINATION ${INSTALL_BIN_DIR})
