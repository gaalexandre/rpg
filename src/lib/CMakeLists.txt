set(LIB_FILES lib.cpp)

add_library(lib ${LIB_FILES})

target_include_directories(lib
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )
