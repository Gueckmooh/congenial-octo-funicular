include(GenerateExportHeader)

add_library(crafting_interpreters_cpp_generator)

file(GLOB_RECURSE SOURCES src/*.cpp)
target_sources(crafting_interpreters_cpp_generator
  PUBLIC
  FILE_SET module_sources
  TYPE CXX_MODULES
  FILES ${SOURCES})

add_library(crafting_interpreters::cpp_generator ALIAS crafting_interpreters_cpp_generator)

target_link_libraries(crafting_interpreters_cpp_generator
    PRIVATE
    crafting_interpreters::options
    crafting_interpreters::warnings
)

target_include_directories(crafting_interpreters_cpp_generator
  ${WARNING_GUARDS}
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
)

target_compile_features(crafting_interpreters_cpp_generator
  PUBLIC cxx_std_23
)

set_target_properties(crafting_interpreters_cpp_generator
  PROPERTIES
  VERSION ${PROJECT_VERSION}
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN YES
  DOC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include
)

generate_export_header(crafting_interpreters_cpp_generator
  BASE_NAME cpp_generator
  EXPORT_FILE_NAME
  ${PROJECT_BINARY_DIR}/include/crafting_interpreters/cpp_generator/export.hpp
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(crafting_interpreters_cpp_generator
    PUBLIC CPP_GENERATOR_STATIC_DEFINE
  )
endif()

# if(BUILD_TESTING AND PROJECT_IS_TOP_LEVEL)
#   add_subdirectory(test)
# endif()

export_target(crafting_interpreters_cpp_generator)
