include(cmake/CPM.cmake)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(crafting_interpreters_setup_dependencies)
  # Needed by unit tests
  if(BUILD_TESTING AND PROJECT_IS_TOP_LEVEL)
    message(STATUS "Getting Catch2 because build testing is enabled")
    if(NOT TARGET Catch2::Catch2WithMain)
      cpmaddpackage("gh:catchorg/Catch2@3.3.2")
    endif()
  endif()

  if(NOT TARGET CLI11::CLI11)
    cpmaddpackage("gh:CLIUtils/CLI11@2.4.2")
  endif()

  if(NOT TARGET tree-sitter)
    cpmaddpackage(
      NAME tree-sitter
      GIT_REPOSITORY https://github.com/tree-sitter/tree-sitter.git
      VERSION 0.24.4
      SOURCE_SUBDIR lib
    )
  endif()

endfunction()
