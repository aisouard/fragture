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

project(common)

add_subdirectory(module)

set(SOURCES
        common.h
        common.cpp)

add_library(common STATIC ${SOURCES})
target_link_libraries(common common_module)

if (BUILD_TESTS)
    set(UNITTEST_SOURCES
            common_unittest.cpp)

    add_executable(common_unittest ${UNITTEST_SOURCES})
    target_link_libraries(common_unittest
            ${GTEST_BOTH_LIBRARIES})

    add_test(CommonUnittest common_unittest)
    set(SOURCES ${SOURCES} ${UNITTEST_SOURCES})
endif (BUILD_TESTS)

set(SOURCES ${SOURCES} main.cpp)
add_style_check_target(common_style "${SOURCES}")