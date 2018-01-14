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

find_package(PkgConfig)
pkg_check_modules(PC_LUAJIT luajit)

find_path(LUAJIT_INCLUDE_DIR luajit.h
        HINTS ${PC_LUAJIT_INCLUDEDIR} ${PC_LUAJIT_INCLUDE_DIRS})
find_library(LUAJIT_LIBRARIES NAMES luajit-5.1
        HINTS ${PC_LUAJIT_LIBDIR} ${PC_LUAJIT_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LuaJIT
        REQUIRED_VARS LUAJIT_LIBRARIES LUAJIT_INCLUDE_DIR
        VERSION_VAR LUAJIT_VERSION_STRING
        FAIL_MESSAGE "${ERROR_MESSAGE}")

mark_as_advanced(LUAJIT_INCLUDE_DIR LUAJIT_LIBRARIES)