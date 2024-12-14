add_executable(grammar_generator)

file(GLOB_RECURSE SOURCES src/*.cpp)
target_sources(grammar_generator PRIVATE ${SOURCES})

target_link_libraries(grammar_generator
  PRIVATE
  crafting_interpreters::warnings
  crafting_interpreters::options

  crafting_interpreters::utilities
  crafting_interpreters::cpp_generator

  CLI11::CLI11

  tree-sitter
  tree-sitter-grammar
)

set_target_properties(grammar_generator
  PROPERTIES
  CXX_SCAN_FOR_MODULES yes
)

target_include_directories(grammar_generator
  ${WARNING_GUARDS}
  PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  ${tree-sitter_SOURCE_DIR}/include
)

# Put it in build/bin
export_target(grammar_generator)
