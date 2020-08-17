cmake_minimum_required(VERSION 3.16.0)
project(RemoteInput VERSION 1.0.0 LANGUAGES C CXX)

# Prep
set(CMAKE_CXX_EXTENSION OFF)
set(DEFAULT_FLAGS "")
set(TEST_FLAGS    "")
set(QUITE_FLAGS   "")

# Provide these ahead of time.
option(BUILD_QUIET     "Shuts up the compiler :)"           OFF)
option(BUILD_DEBUGGING "Enables build debugging."           OFF)
option(BUILD_SHARED    "Enables shared library build."      OFF)
option(BUILD_TESTS     "Builds the tests for this project." OFF)

# Set based on common compilers.
if(CMAKE_CXX_COMPILER_ID MATCHES GNU OR CMAKE_CXX_COMPILER_ID MATCHES Clang)
  # Set defaults.
  set(DEFAULT_FLAGS "${DEFAULT_FLAGS} --std=c++2a -Wall -Wextra -Wpedantic -Wno-unknown-pragmas")

  # Set build specifics.
  if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(DEFAULT_FLAGS "${DEFAULT_FLAGS} -g -O0")
  elseif(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
    set(DEFAULT_FLAGS "${DEFAULT_FLASG} -g -O2")
  elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set(DEFAULT_FLAGS "${DEFAULT_FLAGS} -O3")
  endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
  # Set defaults
  set(DEFAULT_FLAGS "${DEFAULT_FLAGS} /std:c++latest /Wall /Zc:__cplusplus")

  # Set build specifics
  if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(DEFAULT_FLAGS "${DEFAULT_FLAGS} /DEBUG /Od")
  elseif(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
    set(DEFAULT_FLAGS "${DEFAULT_FLAGS} /DEBUG /O1")
  elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set(DEFAULT_FLAGS "${DEFAULT_FLAGS} /Ox")
  endif()
endif()

if(BUILD_QUIET)
  message(STATUS "Quiet build enabled")
  set(DEFAULT_FLAGS "${DEFAULT_FLAGS} ${QUIET_FLAGS}")
endif()

if(BUILD_DEBUGGING)
  message(STATUS "Debugging build enabled")
  if(CMAKE_CXX_COMPILER_ID MATCHES GNU OR CMAKE_CXX_COMPILER_ID MATCHES Clang)
    set(DEFAULT_FLAGS "${DEFAULT_FLAGS} -DREMINPUT_DEBUG")
  elseif(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(DEFAULT_FLAGS "${DEFAULT_FLAGS} /DREMINPUT_DEBUG")
  endif()
endif()

if(BUILD_SHARED)
  message(STATUS "Shared build enabled")
  if(CMAKE_CXX_COMPILER_ID MATCHES GNU OR CMAKE_CXX_COMPILER_ID MATCHES Clang)
    set(DEFAULT_FLAGS "${DEFAULT_FLAGS} -DREMINPUT_SHARED_EXPORT -DSIMULAR_SHARED_EXPORT")
    set(TEST_FLAGS    "${DEFAULT_FLAGS} -DREMINPUT_SHARED_IMPORT -DSIMULAR_SHARED_IMPORT")
  elseif(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(DEFAULT_FLAGS "${DEFAULT_FLAGS} /DREMINPUT_SHARED_EXPORT /DSIMULAR_SHARED_EXPORT")
    set(TEST_FLAGS    "${DEFAULT_FLAGS} /DREMINPUT_SHARED_IMPORT /DSIMULAR_SHARED_IMPORT")
  endif()
endif()

# Set our specific compiler options after we deal with openssl.
set(CMAKE_CXX_FLAGS "${DEFAULT_FLAGS}")

# Set library name
if(CMAKE_BUILD_TYPE MATCHES Debug)
  message(STATUS "Debug build type chosen")
  set(REMINPUT_LIBNAME "reminput_debug")
elseif(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
  message(STATUS "Release with debug info build type chosen")
  set(REMINPUT_LIBNAME "reminput_dev")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
  message(STATUS "Release build type chosen")
  set(REMINPUT_LIBNAME "reminput")
endif()

# Build source if available.
add_subdirectory(source)

# Build tests.
if(BUILD_TESTS)
  set(CMAKE_CXX_FLAGS "${TEST_FLAGS}")
  message(STATUS "Source testing enabled")
  add_subdirectory(tests)
endif()
