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

project(fragture)
cmake_minimum_required(VERSION 3.5)

set(FRAGTURE_VERSION 1.0.0)
set(FRAGTURE_MAJOR_VERSION 1)
set(FRAGTURE_MINOR_VERSION 0)
set(FRAGTURE_PATCH_VERSION 0)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-Dnullptr=NULL)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(LIBUV_USE_STATIC 1)
find_package(LibUV REQUIRED)
find_package(ICU COMPONENTS uc REQUIRED)
find_package(Threads REQUIRED)

include(ExternalProject)
include(CppLint)
include(GitDefinitions)
include(DetectArch)
include(Package)

if (BUILD_TESTS)
    enable_testing()
    ExternalProject_Add(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            UPDATE_COMMAND ""
            INSTALL_COMMAND ""
            LOG_DOWNLOAD ON
            LOG_CONFIGURE ON
            LOG_BUILD ON)

    ExternalProject_Get_Property(googletest source_dir)
    set(GTEST_INCLUDE_DIRS ${source_dir}/googletest/include)
    set(GMOCK_INCLUDE_DIRS ${source_dir}/googlemock/include)

    include_directories(${GTEST_INCLUDE_DIRS})
endif (BUILD_TESTS)

add_subdirectory(src)