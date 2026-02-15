# tuna is a header-only library (heavily templated, like the real STL)
add_library(tuna_tuna INTERFACE)
add_library(tuna::tuna ALIAS tuna_tuna)

target_include_directories(tuna_tuna
  INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

target_link_libraries(tuna_tuna
  INTERFACE
    tuna::tuna_options
    tuna::tuna_warnings)
