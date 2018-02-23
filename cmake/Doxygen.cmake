option(BUILD_DOCUMENTATION "Build documentation" ON)

if(NOT BUILD_DOCUMENTATION)
    return()
endif(NOT BUILD_DOCUMENTATION)

find_package(Doxygen)
if(NOT DOXYGEN_FOUND)
    message("Doxygen must be installed to generate the documentation")
    return()
endif(NOT DOXYGEN_FOUND)

set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile)

configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
message("Doxygen build started")

add_custom_target(docs ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs/html DESTINATION share/doc)
