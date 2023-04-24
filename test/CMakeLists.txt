cmake_minimum_required(VERSION 3.13)

include(FetchContent)
FetchContent_Declare(gtest
  QUIET
  URL https://github.com/google/googletest/archive/release-1.11.0.tar.gz
)
# configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/test)

set(COMMON_LIBS example ${EXTERNAL_LIBS} gtest gtest_main dl pthread)
cxx_executable_with_flags(example_add_test "" "${COMMON_LIBS}" "example_add.cpp")
cxx_executable_with_flags(example_subtract_test "" "${COMMON_LIBS}" "example_subtract.cpp")
cxx_executable_with_flags(example_common_test "" "${COMMON_LIBS}" "example_common.cpp")

# build google test list
set(TEST_TARGETS
  example_add_test
  example_subtract_test
  example_common_test
)

foreach(target ${TEST_TARGETS})
  gtest_discover_tests(${target} WORKING_DIRECTORY ${TEST_BIN_PATH})
endforeach()
