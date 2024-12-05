macro(crafting_interpreters_declare_options)
  set(MAYBE_ON ${PROJECT_IS_TOP_LEVEL})

  option(crafting_interpreters_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ${MAYBE_ON})
  option(crafting_interpreters_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  option(crafting_interpreters_ENABLE_CLANG_TIDY "Enable clang-tidy check" OFF)
  option(crafting_interpreters_ENABLE_DOCUMENTATION "Enable documentation generation" OFF)

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      crafting_interpreters_WARNINGS_AS_ERRORS
      crafting_interpreters_ENABLE_COVERAGE
      crafting_interpreters_ENABLE_CLANG_TIDY
      crafting_interpreters_ENABLE_DOCUMENTATION
    )
  endif()
endmacro()

macro(crafting_interpreters_process_options)
  if(PROJECT_IS_TOP_LEVEL)
    include(cmake/StandardProjectSettings.cmake)
  endif()

  add_library(crafting_interpreters_warnings INTERFACE)
  add_library(crafting_interpreters_options INTERFACE)

  add_library(crafting_interpreters::options ALIAS crafting_interpreters_options)
  add_library(crafting_interpreters::warnings ALIAS crafting_interpreters_warnings)

  include(cmake/CompilerWarnings.cmake)
  crafting_interpreters_set_project_warnings(
    crafting_interpreters_warnings
    ${crafting_interpreters_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

  if(crafting_interpreters_ENABLE_COVERAGE)
    include(cmake/Coverage.cmake)
    crafting_interpreters_enable_coverage(crafting_interpreters_options)
  endif()

  if(crafting_interpreters_ENABLE_CLANG_TIDY)
    include(cmake/ClangTidy.cmake)
    crafting_interpreters_enable_clang_tidy(crafting_interpreters_options crafting_interpreters_WARNING_AS_ERRORS)
  endif()

  set_target_properties(crafting_interpreters_options PROPERTIES CXX_VISIBILITY_PRESET hidden)
endmacro()

macro(crafting_interpreters_setup_options)
  crafting_interpreters_declare_options()
  crafting_interpreters_process_options()
endmacro()
