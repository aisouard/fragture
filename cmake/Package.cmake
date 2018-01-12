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

#
# Create package
set(CPACK_PACKAGE_FILE_NAME "fragture-${FRAGTURE_VERSION}-${TARGET_OS}-${TARGET_CPU}")

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Fragture game engine")
set(CPACK_PACKAGE_DESCRIPTION "Just experimenting a multithreaded game engine")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")

set(CPACK_PACKAGE_NAME "fragture")
set(CPACK_PACKAGE_VERSION "${FRAGTURE_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${FRAGTURE_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${FRAGTURE_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "${FRAGTURE_PATCH_VERSION}")

set(CPACK_PACKAGE_VENDOR "Axel Isouard")
set(CPACK_PACKAGE_CONTACT "axel@isouard.fr")

if (WIN32)
    set(CPACK_GENERATOR "ZIP")
else (WIN32)
    set(CPACK_GENERATOR "TGZ")
endif (WIN32)

if (UNIX AND NOT APPLE)
    if (TARGET_CPU STREQUAL "x86")
        set(_RPM_ARCH "i686")
        set(_DEB_ARCH "i386")
    elseif (TARGET_CPU STREQUAL "x64")
        set(_RPM_ARCH "x86_64")
        set(_DEB_ARCH "amd64")
    elseif (TARGET_CPU STREQUAL "arm")
        set(_RPM_ARCH "armhf")
        set(_DEB_ARCH "armhf")
    elseif (TARGET_CPU STREQUAL "arm64")
        set(_RPM_ARCH "aarch64")
        set(_DEB_ARCH "arm64")
    else ()
        set(_RPM_ARCH ${CMAKE_SYSTEM_PROCESSOR})
        set(_DEB_ARCH ${CMAKE_SYSTEM_PROCESSOR})
    endif ()

    set(CPACK_PACKAGE_FILE_NAME "fragture-${FRAGTURE_VERSION}")
    if (CPACK_GENERATOR STREQUAL "RPM")
        set(_PACKAGE_ARCH ${_RPM_ARCH})
    elseif (CPACK_GENERATOR STREQUAL "DEB")
        set(_PACKAGE_ARCH ${_DEB_ARCH})
    else ()
        set(_PACKAGE_ARCH ${TARGET_CPU})
        set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-${TARGET_OS}")
    endif ()

    if (BUILD_DEB_PACKAGE)
        set(CPACK_DEB_COMPONENT_INSTALL FALSE)
        set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
        set(CPACK_DEBIAN_PACKAGE_SECTION "libs")
        set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://axel.isouard.fr/fragture")
        set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS TRUE)
        set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "${_PACKAGE_ARCH}")
        set(CPACK_GENERATOR "${CPACK_GENERATOR};DEB")
    endif (BUILD_DEB_PACKAGE)

    if (BUILD_RPM_PACKAGE)
        set(CPACK_RPM_COMPONENT_INSTALL FALSE)
        set(CPACK_RPM_PACKAGE_SUMMARY ${CPACK_PACKAGE_DESCRIPTION_SUMMARY})
        set(CPACK_RPM_PACKAGE_DESCRIPTION ${CPACK_PACKAGE_DESCRIPTION})
        set(CPACK_RPM_PACKAGE_URL "https://axel.isouard.fr/fragture")
        set(CPACK_RPM_PACKAGE_LICENSE "Apache-2.0")
        set(CPACK_RPM_PACKAGE_ARCHITECTURE "${_PACKAGE_ARCH}")
        set(CPACK_GENERATOR "${CPACK_GENERATOR};RPM")
    endif (BUILD_RPM_PACKAGE)

    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-${_PACKAGE_ARCH}")
    set(CPACK_SOURCE_PACKAGE_FILE_NAME "fragture-${FRAGTURE_VERSION}-${_PACKAGE_ARCH}")
endif (UNIX AND NOT APPLE)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_FILE_NAME}-debug)
endif (CMAKE_BUILD_TYPE MATCHES Debug)

set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)
set(CPACK_PACKAGE_INSTALL_DIRECTORY "fragture")

include(CPack)