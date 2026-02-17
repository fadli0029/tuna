include(cmake/CPM.cmake)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other targets
function(tuna_setup_dependencies)

  # Test and benchmark dependencies are only needed when building
  # tuna as the top-level project. When consumed as a sub-project,
  # the CMakeLists.txt returns before adding test/bench subdirs.
  if(NOT PROJECT_IS_TOP_LEVEL)
    return()
  endif()

  if(NOT TARGET Catch2::Catch2WithMain)
    cpmaddpackage(
      NAME Catch2
      VERSION 3.12.0
      GITHUB_REPOSITORY catchorg/Catch2
      EXCLUDE_FROM_ALL YES
      SYSTEM YES)
  endif()

  if(NOT TARGET benchmark::benchmark)
    cpmaddpackage(
      NAME benchmark
      VERSION 1.9.5
      GITHUB_REPOSITORY google/benchmark
      EXCLUDE_FROM_ALL YES
      SYSTEM YES
      OPTIONS "BENCHMARK_ENABLE_TESTING OFF")
  endif()

endfunction()
