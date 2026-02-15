include(cmake/CPM.cmake)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other targets
function(tuna_setup_dependencies)

  if(NOT TARGET Catch2::Catch2WithMain)
    cpmaddpackage("gh:catchorg/Catch2@3.12.0")
  endif()

  if(NOT TARGET benchmark::benchmark)
    cpmaddpackage(
      NAME
      benchmark
      VERSION
      1.9.5
      GITHUB_REPOSITORY
      "google/benchmark"
      OPTIONS
      "BENCHMARK_ENABLE_TESTING OFF")
  endif()


endfunction()
