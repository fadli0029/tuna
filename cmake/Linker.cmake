macro(tuna_configure_linker project_name)
  set(tuna_USER_LINKER_OPTION
    "DEFAULT"
      CACHE STRING "Linker to be used")
    set(tuna_USER_LINKER_OPTION_VALUES "DEFAULT" "SYSTEM" "LLD" "GOLD" "BFD" "MOLD" "SOLD" "APPLE_CLASSIC" "MSVC")
  set_property(CACHE tuna_USER_LINKER_OPTION PROPERTY STRINGS ${tuna_USER_LINKER_OPTION_VALUES})
  list(
    FIND
    tuna_USER_LINKER_OPTION_VALUES
    ${tuna_USER_LINKER_OPTION}
    tuna_USER_LINKER_OPTION_INDEX)

  if(${tuna_USER_LINKER_OPTION_INDEX} EQUAL -1)
    message(
      STATUS
        "Using custom linker: '${tuna_USER_LINKER_OPTION}', explicitly supported entries are ${tuna_USER_LINKER_OPTION_VALUES}")
  endif()

  set_target_properties(${project_name} PROPERTIES LINKER_TYPE "${tuna_USER_LINKER_OPTION}")
endmacro()
