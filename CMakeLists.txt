cmake_minimum_required(VERSION 3.29)

# C++23 strictly
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the project name and language
project(
  tuna
  VERSION 0.0.1
  DESCRIPTION "A from-scratch reimplementation of the C++ standard library"
  HOMEPAGE_URL "https://github.com/fadliov/tuna"
  LANGUAGES CXX)

include(cmake/PreventInSourceBuilds.cmake)
include(ProjectOptions.cmake)

tuna_setup_options()

tuna_global_options()
include(Dependencies.cmake)
tuna_setup_dependencies()

tuna_local_options()

target_compile_features(tuna_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

add_library(tuna::tuna_options ALIAS tuna_options)
add_library(tuna::tuna_warnings ALIAS tuna_warnings)

# Adding the src:
add_subdirectory(src)

# Don't even look at tests if we're not top level
if(NOT PROJECT_IS_TOP_LEVEL)
  return()
endif()

# Adding the tests:
include(CTest)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()

# Adding the benchmarks:
option(tuna_BUILD_BENCHMARKS "Build benchmark executables" ON)
if(tuna_BUILD_BENCHMARKS)
  add_subdirectory(bench)
endif()

if(tuna_BUILD_FUZZ_TESTS)
  message(AUTHOR_WARNING "Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html")
  if(NOT tuna_ENABLE_SANITIZER_ADDRESS AND NOT tuna_ENABLE_SANITIZER_THREAD)
    message(WARNING "You need asan or tsan enabled for meaningful fuzz testing")
  endif()
  add_subdirectory(fuzz_test)
endif()
