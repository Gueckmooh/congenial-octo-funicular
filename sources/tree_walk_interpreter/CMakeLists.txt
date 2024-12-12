add_executable(tlox)

file(GLOB_RECURSE SOURCES src/*.cpp)
target_sources(tlox PRIVATE ${SOURCES})

target_link_libraries(tlox
  PRIVATE
  crafting_interpreters::warnings
  crafting_interpreters::options

  crafting_interpreters::utilities

  # Command line interface
  CLI11::CLI11
)

# Put it in build/bin
export_target(tlox)
