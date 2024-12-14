add_executable(crafting_interpreters_library_cxx20_module_test)

file(GLOB_RECURSE SOURCES *.cpp)
target_sources(crafting_interpreters_library_cxx20_module_test PRIVATE ${SOURCES})

target_link_libraries(crafting_interpreters_library_cxx20_module_test
  PRIVATE
  crafting_interpreters::warnings
  crafting_interpreters::options
  crafting_interpreters::library_cxx20_module

  Catch2::Catch2WithMain
)

include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)
catch_discover_tests(crafting_interpreters_library_cxx20_module_test)
