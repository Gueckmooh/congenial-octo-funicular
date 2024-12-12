add_executable(grammar_generator)

file(GLOB_RECURSE SOURCES src/*.cpp)
target_sources(grammar_generator PRIVATE ${SOURCES})

add_subdirectory(tree-sitter-grammar)

target_link_libraries(grammar_generator
  PRIVATE
  crafting_interpreters::warnings
  crafting_interpreters::options

  crafting_interpreters::utilities

  tree-sitter
  tree-sitter-grammar
)

target_include_directories(grammar_generator
  ${WARNING_GUARDS}
  PRIVATE
  ${tree-sitter_SOURCE_DIR}/include
)

# Put it in build/bin
export_target(grammar_generator)
