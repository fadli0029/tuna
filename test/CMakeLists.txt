cmake_minimum_required(VERSION 3.15...3.23)

project(CmakeConfigPackageTests
  VERSION ${PROJECT_VERSION}
  LANGUAGES CXX)

# ---- Test as standalone project the exported config package ----

if(PROJECT_IS_TOP_LEVEL OR TEST_INSTALLED_VERSION)
  enable_testing()

  find_package(tuna CONFIG REQUIRED)

  if(NOT TARGET tuna_options)
    message(FATAL_ERROR "Required config package not found!")
    return()
  endif()
endif()

# ---- Dependencies ----

include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

# ---- Tests ----

# Example:
#
# add_executable(vector_tests vector_tests.cpp)
# target_link_libraries(vector_tests
#   PRIVATE
#     tuna::tuna_warnings
#     tuna::tuna_options
#     tuna::tuna
#     Catch2::Catch2WithMain)
#
# tuna_configure_linker(vector_tests)
#
# catch_discover_tests(vector_tests
#   TEST_PREFIX "vector."
#   REPORTER XML
#   OUTPUT_DIR .
#   OUTPUT_PREFIX "vector."
#   OUTPUT_SUFFIX .xml)
