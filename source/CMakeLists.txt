include_directories(${PROJECT_SOURCE_DIR}/include/)
file(GLOB_RECURSE SOURCES false "./" "*.cpp")
if(BUILD_SHARED)
  add_library(${REMINPUT_LIBNAME} SHARED ${SOURCES})
else()
  add_library(${REMINPUT_LIBNAME} STATIC ${SOURCES})
endif()
if(BUILD_SHARED)
  set_target_properties(
    ${REMINPUT_LIBNAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_SOURCE_DIR}/bin/
  )
endif()
set_target_properties(
  ${REMINPUT_LIBNAME} PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY
  ${PROJECT_SOURCE_DIR}/lib/
)