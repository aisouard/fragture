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

ExternalProject_Add(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.8.0
        UPDATE_COMMAND ""
        INSTALL_DIR "${CMAKE_BINARY_DIR}/googletest-prefix/src/googletest-install"
        CMAKE_ARGS
        -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/googletest-prefix/src/googletest-install/${CMAKE_BUILD_TYPE}
        LOG_DOWNLOAD ON
        LOG_CONFIGURE ON
        LOG_INSTALL ON
        LOG_BUILD ON)

ExternalProject_Get_Property(googletest install_dir)

set(GTEST_INCLUDE_DIRS ${install_dir}/${CMAKE_BUILD_TYPE}/include)
include_directories(${GTEST_INCLUDE_DIRS})

set(GTEST_LIBRARY gtest)
add_library(${GTEST_LIBRARY} STATIC IMPORTED)
set_property(TARGET ${GTEST_LIBRARY} PROPERTY IMPORTED_LOCATION_DEBUG
        "${install_dir}/Debug/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${GTEST_LIBRARY}${CMAKE_STATIC_LIBRARY_SUFFIX}")
set_property(TARGET ${GTEST_LIBRARY} PROPERTY IMPORTED_LOCATION_RELEASE
        "${install_dir}/Release/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${GTEST_LIBRARY}${CMAKE_STATIC_LIBRARY_SUFFIX}")
add_dependencies(${GTEST_LIBRARY} googletest)

set(GTEST_MAIN_LIBRARY gtest_main)
add_library(${GTEST_MAIN_LIBRARY} STATIC IMPORTED)
set_property(TARGET ${GTEST_MAIN_LIBRARY} PROPERTY IMPORTED_LOCATION_DEBUG
        "${install_dir}/Debug/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${GTEST_MAIN_LIBRARY}${CMAKE_STATIC_LIBRARY_SUFFIX}")
set_property(TARGET ${GTEST_MAIN_LIBRARY} PROPERTY IMPORTED_LOCATION_RELEASE
        "${install_dir}/Release/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${GTEST_MAIN_LIBRARY}${CMAKE_STATIC_LIBRARY_SUFFIX}")
add_dependencies(${GTEST_MAIN_LIBRARY} googletest)

set(GTEST_BOTH_LIBRARIES ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})