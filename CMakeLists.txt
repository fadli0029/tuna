cmake_minimum_required(VERSION 3.29)

# This template attempts to be "fetch_content"-able
# so that it works well with tools like CPM or other
# manual dependency management

# C++23 strictly
set(CMAKE_CXX_STANDARD 23)

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
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

set(GIT_SHA
    "Unknown"
    CACHE STRING "SHA this build was generated from")
string(
  SUBSTRING "${GIT_SHA}"
            0
            8
            GIT_SHORT_SHA)

target_compile_features(tuna_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

add_library(tuna::tuna_options ALIAS tuna_options)
add_library(tuna::tuna_warnings ALIAS tuna_warnings)

# configure files based on CMake configuration options
add_subdirectory(configured_files)

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

# If MSVC is being used, and ASAN is enabled, we need to set the debugger environment
# so that it behaves well with MSVC's debugger, and we can run the target from visual studio
if(MSVC)
  get_all_installable_targets(all_targets)
  message("all_targets=${all_targets}")
  set_target_properties(${all_targets} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=$(VC_ExecutablePath_x64);%PATH%")
endif()

if(CMAKE_SKIP_INSTALL_RULES)
  return()
endif()

include(cmake/PackageProject.cmake)

tuna_package_project(
  TARGETS
  tuna_tuna
  tuna_options
  tuna_warnings
)

set(CPACK_PACKAGE_FILE_NAME
    "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${GIT_SHORT_SHA}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}"
)

include(CPack)
