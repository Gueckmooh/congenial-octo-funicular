if(NOT crafting_interpreters_ENABLE_DOCUMENTATION)
  return()
endif()

message(STATUS "Configuring documentation generation")
find_package(Doxygen REQUIRED)

set(DOXUGEN_INPUT_DIR "")
set(HEADER_DEPENDENCIES "")

get_all_targets_recursive(ALL_TARGETS ${PROJECT_SOURCE_DIR}/sources)
foreach(TARGET IN ITEMS ${ALL_TARGETS})
    get_target_property(INCLUDE_DIR ${TARGET} DOC_INCLUDE_DIR)
    if(NOT ${INCLUDE_DIR} STREQUAL INCLUDE_DIR-NOTFOUND)
        set(DOXYGEN_INPUT_DIR "${DOXYGEN_INPUT_DIR} ${INCLUDE_DIR}")
        file(GLOB_RECURSE MODULE_PUBLIC_HEADERS ${INCLUDE_DIR}/**/*.hpp)
        list(APPEND HEADER_DEPENDENCIES "${MODULE_PUBLIC_HEADERS}")
    endif()
endforeach()

message(STATUS "The dependencies are ${HEADER_DEPENDENCIES}")

set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(DOXYGEN_INCLUDE_PATH "${CMAKE_BINARY_DIR}/include ${DOXYGEN_INPUT_DIR}")
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

#Replace variables inside @@ with the current values
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR}) #Doxygen won't create this for us
add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                   DEPENDS ${HEADER_DEPENDENCIES}
                   COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                   MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
                   COMMENT "Generating docs in ${DOXYGEN_OUTPUT_DIR}")

add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})
