cmake_minimum_required(VERSION 3.2)

project(ip_filter_test_driven VERSION 0.0.1)

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

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

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

install(TARGETS ip_filter_test_driven RUNTIME DESTINATION bin)

message("${PROJECT_NAME} build ${PROJECT_VERSION}")

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT alexandr_kudinov@mail.ru)

include(CPack)
