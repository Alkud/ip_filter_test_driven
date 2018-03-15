cmake_minimum_required(VERSION 3.2)

project(ip_filter_test_driven)

add_executable(${PROJECT_NAME} "main.cpp")

add_library(process process.cpp)

add_executable(ip_filter_boost_test ip_filter_boost_test.cpp)

set (BOOST_MIN_VERSION "1.54.0")

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

enable_testing()
add_test(
  NAME boost_test
  COMMAND ip_filter_boost_test
)

set_target_properties(ip_filter_test_driven
  PROPERTIES CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

set_target_properties(ip_filter_boost_test PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(ip_filter_test_driven process)

target_link_libraries(ip_filter_boost_test
  ${Boost_LIBRARIES}
  process
)
