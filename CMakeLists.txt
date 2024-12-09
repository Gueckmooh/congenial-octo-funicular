cmake_minimum_required(VERSION 3.21)

# This template attempts to be "fetch_content"-able
# so that it works well with tools like CPM or other
# manual dependency management
# It is inspired by lefticus' one

# Set the cxx_standard if it is not set by someone else
if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 23)
endif()

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the project name and language
project(
  crafting_interpreters
  VERSION 0.0.1
  DESCRIPTION ""
  HOMEPAGE_URL "%%myurl%%"
  LANGUAGES CXX
)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Prevent in source builds
include(cmake/PreventInSourceBuilds.cmake)

# Setup project options
include(ProjectOptions.cmake)
crafting_interpreters_setup_options()

# Include CTest here to access tests from build directory and have BUILD_TESTING
# set
include(CTest)

# Setup project dependencies
include(ProjectDependencies.cmake)
crafting_interpreters_setup_dependencies()

# Include the sources
add_subdirectory(sources)

define_property(TARGET PROPERTY DOC_INCLUDE_DIR
  BRIEF_DOCS "The include directory with headers to document")

add_subdirectory(docs)
