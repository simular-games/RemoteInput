include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

if(WIN32)
  add_executable(wintest wintest.cpp)
  target_link_libraries(wintest PUBLIC ${REMINPUT_LIBNAME})
  set_target_properties(
    wintest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_SOURCE_DIR}/bin
  )
endif()