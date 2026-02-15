include(cmake/SystemLink.cmake)
include(cmake/LibFuzzer.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)


macro(tuna_supports_sanitizers)
  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)

    message(STATUS "Sanity checking UndefinedBehaviorSanitizer, it should be supported on this platform")
    set(TEST_PROGRAM "int main() { return 0; }")

    set(CMAKE_REQUIRED_FLAGS "-fsanitize=undefined")
    set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=undefined")
    check_cxx_source_compiles("${TEST_PROGRAM}" HAS_UBSAN_LINK_SUPPORT)

    if(HAS_UBSAN_LINK_SUPPORT)
      message(STATUS "UndefinedBehaviorSanitizer is supported at both compile and link time.")
      set(SUPPORTS_UBSAN ON)
    else()
      message(WARNING "UndefinedBehaviorSanitizer is NOT supported at link time.")
      set(SUPPORTS_UBSAN OFF)
    endif()
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    if(NOT WIN32)
      message(STATUS "Sanity checking AddressSanitizer, it should be supported on this platform")
      set(TEST_PROGRAM "int main() { return 0; }")

      set(CMAKE_REQUIRED_FLAGS "-fsanitize=address")
      set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=address")
      check_cxx_source_compiles("${TEST_PROGRAM}" HAS_ASAN_LINK_SUPPORT)

      if(HAS_ASAN_LINK_SUPPORT)
        message(STATUS "AddressSanitizer is supported at both compile and link time.")
        set(SUPPORTS_ASAN ON)
      else()
        message(WARNING "AddressSanitizer is NOT supported at link time.")
        set(SUPPORTS_ASAN OFF)
      endif()
    else()
      set(SUPPORTS_ASAN ON)
    endif()
  endif()
endmacro()

macro(tuna_setup_options)
  option(tuna_ENABLE_HARDENING "Enable hardening" ON)
  option(tuna_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  cmake_dependent_option(
    tuna_ENABLE_GLOBAL_HARDENING
    "Attempt to push hardening options to built dependencies"
    ON
    tuna_ENABLE_HARDENING
    OFF)

  tuna_supports_sanitizers()

  if(NOT PROJECT_IS_TOP_LEVEL OR tuna_PACKAGING_MAINTAINER_MODE)
    option(tuna_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(tuna_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(tuna_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(tuna_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(tuna_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(tuna_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(tuna_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(tuna_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(tuna_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(tuna_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(tuna_ENABLE_PCH "Enable precompiled headers" OFF)
    option(tuna_ENABLE_CACHE "Enable ccache" OFF)
  else()
    option(tuna_ENABLE_IPO "Enable IPO/LTO" ON)
    option(tuna_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
    option(tuna_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
    option(tuna_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(tuna_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
    option(tuna_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(tuna_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(tuna_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(tuna_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
    option(tuna_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(tuna_ENABLE_PCH "Enable precompiled headers" OFF)
    option(tuna_ENABLE_CACHE "Enable ccache" ON)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      tuna_ENABLE_IPO
      tuna_WARNINGS_AS_ERRORS
      tuna_ENABLE_SANITIZER_ADDRESS
      tuna_ENABLE_SANITIZER_LEAK
      tuna_ENABLE_SANITIZER_UNDEFINED
      tuna_ENABLE_SANITIZER_THREAD
      tuna_ENABLE_SANITIZER_MEMORY
      tuna_ENABLE_UNITY_BUILD
      tuna_ENABLE_CLANG_TIDY
      tuna_ENABLE_CPPCHECK
      tuna_ENABLE_COVERAGE
      tuna_ENABLE_PCH
      tuna_ENABLE_CACHE)
  endif()

  tuna_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
  if(LIBFUZZER_SUPPORTED AND (tuna_ENABLE_SANITIZER_ADDRESS OR tuna_ENABLE_SANITIZER_THREAD OR tuna_ENABLE_SANITIZER_UNDEFINED))
    set(DEFAULT_FUZZER ON)
  else()
    set(DEFAULT_FUZZER OFF)
  endif()

  option(tuna_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

macro(tuna_global_options)
  if(tuna_ENABLE_IPO)
    include(cmake/InterproceduralOptimization.cmake)
    tuna_enable_ipo()
  endif()

  tuna_supports_sanitizers()

  if(tuna_ENABLE_HARDENING AND tuna_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN
       OR tuna_ENABLE_SANITIZER_UNDEFINED
       OR tuna_ENABLE_SANITIZER_ADDRESS
       OR tuna_ENABLE_SANITIZER_THREAD
       OR tuna_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${tuna_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${tuna_ENABLE_SANITIZER_UNDEFINED}")
    tuna_enable_hardening(tuna_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()
endmacro()

macro(tuna_local_options)
  if(PROJECT_IS_TOP_LEVEL)
    include(cmake/StandardProjectSettings.cmake)
  endif()

  add_library(tuna_warnings INTERFACE)
  add_library(tuna_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  tuna_set_project_warnings(
    tuna_warnings
    ${tuna_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

  include(cmake/Linker.cmake)

  include(cmake/Sanitizers.cmake)
  tuna_enable_sanitizers(
    tuna_options
    ${tuna_ENABLE_SANITIZER_ADDRESS}
    ${tuna_ENABLE_SANITIZER_LEAK}
    ${tuna_ENABLE_SANITIZER_UNDEFINED}
    ${tuna_ENABLE_SANITIZER_THREAD}
    ${tuna_ENABLE_SANITIZER_MEMORY})

  set_target_properties(tuna_options PROPERTIES UNITY_BUILD ${tuna_ENABLE_UNITY_BUILD})

  if(tuna_ENABLE_PCH)
    target_precompile_headers(
      tuna_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(tuna_ENABLE_CACHE)
    include(cmake/Cache.cmake)
    tuna_enable_cache()
  endif()

  include(cmake/StaticAnalyzers.cmake)
  if(tuna_ENABLE_CLANG_TIDY)
    tuna_enable_clang_tidy(tuna_options ${tuna_WARNINGS_AS_ERRORS})
  endif()

  if(tuna_ENABLE_CPPCHECK)
    tuna_enable_cppcheck(${tuna_WARNINGS_AS_ERRORS} "")
  endif()

  if(tuna_ENABLE_COVERAGE)
    include(cmake/Tests.cmake)
    tuna_enable_coverage(tuna_options)
  endif()

  if(tuna_WARNINGS_AS_ERRORS)
    check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
    if(LINKER_FATAL_WARNINGS)
      # This is not working consistently, so disabling for now
      # target_link_options(tuna_options INTERFACE -Wl,--fatal-warnings)
    endif()
  endif()

  if(tuna_ENABLE_HARDENING AND NOT tuna_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN
       OR tuna_ENABLE_SANITIZER_UNDEFINED
       OR tuna_ENABLE_SANITIZER_ADDRESS
       OR tuna_ENABLE_SANITIZER_THREAD
       OR tuna_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    tuna_enable_hardening(tuna_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
