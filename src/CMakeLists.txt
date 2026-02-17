include(GNUInstallDirs)

add_library(tuna_tuna INTERFACE)
add_library(tuna::tuna ALIAS tuna_tuna)

target_include_directories(tuna_tuna
  INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

# tuna_options and tuna_warnings are internal build targets (compiler warnings,
# sanitizers, etc.). BUILD_INTERFACE ensures consumers don't inherit them.
target_link_libraries(tuna_tuna
  INTERFACE
    "$<BUILD_INTERFACE:tuna::tuna_options>"
    "$<BUILD_INTERFACE:tuna::tuna_warnings>")

# Install rules -- only when building tuna directly, not when consumed
# via add_subdirectory or FetchContent.
if(PROJECT_IS_TOP_LEVEL)
  include(CMakePackageConfigHelpers)

  install(TARGETS tuna_tuna
    EXPORT tuna-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

  install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/tuna
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

  install(EXPORT tuna-targets
    FILE tuna-targets.cmake
    NAMESPACE tuna::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tuna)

  write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/tuna-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

  configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/tuna-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/tuna-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tuna)

  install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/tuna-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/tuna-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tuna)
endif()
