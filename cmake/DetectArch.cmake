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

include(CheckSymbolExists)

#
# Target OS
set(TARGET_OS "" CACHE STRING "Target OS")
set(TARGET_OS_LIST android ios linux mac win)

if (TARGET_OS STREQUAL "")
    if (CMAKE_SYSTEM_NAME MATCHES "Linux")
        set(TARGET_OS "linux")
    elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
        set(TARGET_OS "mac")
    elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
        set(TARGET_OS "win")
    endif ()
endif (TARGET_OS STREQUAL "")

if (NOT ${TARGET_OS} IN_LIST TARGET_OS_LIST)
    message(FATAL_ERROR "Unknown value '${TARGET_OS}' for variable TARGET_OS, options are: ${TARGET_OS_LIST}")
endif (NOT ${TARGET_OS} IN_LIST TARGET_OS_LIST)

#
# Target CPU
function(detect_current_arch)
    if (WIN32 AND NOT MINGW)
        check_symbol_exists("_M_X64" "" ARCH_X64)
        if (NOT ARCH_X64)
            check_symbol_exists("_M_AMD64" "" ARCH_X64)
        endif (NOT ARCH_X64)
        check_symbol_exists("_M_IX86" "" ARCH_X86)
        check_symbol_exists("_M_ARM" "" ARCH_ARM)
        check_symbol_exists("_M_ARM64" "" ARCH_ARM64)
    else (WIN32 AND NOT MINGW)
        check_symbol_exists("__i386__" "" ARCH_X86)
        check_symbol_exists("__x86_64__" "" ARCH_X64)
        check_symbol_exists("__arm__" "" ARCH_ARM)
        check_symbol_exists("__aarch64__" "" ARCH_ARM64)
    endif (WIN32 AND NOT MINGW)
endfunction(detect_current_arch)

set(TARGET_CPU "" CACHE STRING "Target CPU")
set(TARGET_CPU_LIST x86 x64 arm arm64)

if (TARGET_CPU STREQUAL "")
    detect_current_arch()

    if (ARCH_X64)
        set(TARGET_CPU "x64")
    elseif (ARCH_X86)
        set(TARGET_CPU "x86")
    elseif (ARCH_ARM64)
        set(TARGET_CPU "arm64")
    elseif (ARCH_ARM)
        set(TARGET_CPU "arm")
    else ()
        set(TARGET_CPU ${CMAKE_SYSTEM_PROCESSOR})
    endif (ARCH_X64)
endif (TARGET_CPU STREQUAL "")

if (NOT ${TARGET_CPU} IN_LIST TARGET_CPU_LIST)
    message(FATAL_ERROR "Unknown value '${TARGET_CPU}' for variable TARGET_CPU, options are: ${TARGET_CPU_LIST}")
endif (NOT ${TARGET_CPU} IN_LIST TARGET_CPU_LIST)

message("Building for OS ${TARGET_OS}, arch ${TARGET_CPU}")