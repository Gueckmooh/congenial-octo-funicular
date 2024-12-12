include(GenerateExportHeader)

add_library(crafting_interpreters_utilities)

file(GLOB_RECURSE SOURCES src/*.cpp)
target_sources(crafting_interpreters_utilities PRIVATE ${SOURCES})

add_library(crafting_interpreters::utilities ALIAS crafting_interpreters_utilities)

target_link_libraries(crafting_interpreters_utilities
    PRIVATE
    crafting_interpreters::options
    crafting_interpreters::warnings
)

target_include_directories(crafting_interpreters_utilities
  ${WARNING_GUARDS}
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
)

target_compile_features(crafting_interpreters_utilities
  PUBLIC cxx_std_20
)

set_target_properties(crafting_interpreters_utilities
  PROPERTIES
  VERSION ${PROJECT_VERSION}
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN YES
  DOC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include
)

generate_export_header(crafting_interpreters_utilities
  BASE_NAME utilities
  EXPORT_FILE_NAME
  ${PROJECT_BINARY_DIR}/include/crafting_interpreters/utilities/export.hpp
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(crafting_interpreters_utilities
    PUBLIC UTILITIES_STATIC_DEFINE
  )
endif()

# if(BUILD_TESTING AND PROJECT_IS_TOP_LEVEL)
#   add_subdirectory(test)
# endif()

export_target(crafting_interpreters_utilities)
