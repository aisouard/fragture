# Copyright (C) 2013-2015 Daniel Scharrer
#
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the author(s) be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

find_package(PythonInterp)

set(STYLE_FILTER)

set(STYLE_CHECK_SCRIPT "${CMAKE_SOURCE_DIR}/tools/cpplint.py")

add_custom_target(style)

# Add a target that runs cpplint.py
#
# Parameters:
# - TARGET_NAME the name of the target to add
# - SOURCES_LIST a complete list of source and include files to check
function(add_style_check_target TARGET_NAME SOURCES_LIST)

    if (NOT PYTHONINTERP_FOUND)
        return()
    endif ()

    list(SORT SOURCES_LIST)
    list(REMOVE_DUPLICATES SOURCES_LIST)

    add_custom_target(${TARGET_NAME}
            COMMAND "${CMAKE_COMMAND}" -E chdir
            "${PROJECT_SOURCE_DIR}"
            "${PYTHON_EXECUTABLE}"
            "${STYLE_CHECK_SCRIPT}"
            "--root=${CMAKE_SOURCE_DIR}/src"
            "--quiet"
            ${SOURCES_LIST}
            DEPENDS ${SOURCES_LIST} ${STYLE_CHECK_SCRIPT}
            COMMENT "Checking code style for ${PROJECT_NAME}."
            VERBATIM)

    add_dependencies(style ${TARGET_NAME})
endfunction(add_style_check_target)