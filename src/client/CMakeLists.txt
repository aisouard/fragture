#
# Copyright 2018 Axel Isouard <axel@isouard.fr>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.

project(client)

include_directories(${LIBUV_INCLUDE_DIR})
include_directories(${BREAKPAD_INCLUDE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(SOURCES
        main.cpp)

add_executable(fragture ${SOURCES})
target_link_libraries(fragture
        server
        ${BREAKPAD_LIBRARY}
        ${LIBUV_LIBRARIES})
set_target_properties(fragture PROPERTIES SUFFIX "-${TARGET_CPU}")

add_style_check_target(client_style "${SOURCES}" ${PROJECT_SOURCE_DIR}/..)
add_dependencies(style client_style)

install(TARGETS fragture
        RUNTIME DESTINATION .)