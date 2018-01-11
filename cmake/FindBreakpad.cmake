if (PKG_CONFIG_FOUND)
    pkg_check_modules(PC_BREAKPAD QUIET breakpad-client)
endif (PKG_CONFIG_FOUND)

find_path(BREAKPAD_INCLUDE_DIR
        NAMES google_breakpad/common/breakpad_types.h
        PATH_SUFFIXES breakpad
        HINTS
        ${PC_BREAKPAD_INCLUDEDIR}
        DOC "Google Breakpad include directory")

mark_as_advanced(BREAKPAD_INCLUDE_DIR)
set(BREAKPAD_INCLUDE_DIRS ${BREAKPAD_INCLUDE_DIR})

find_library(BREAKPAD_LIBRARY
        NAMES breakpad_client
        HINTS
        ${PC_BREAKPAD_LIBDIR}
        PATH_SUFFIXES lib${LIB_SUFFIX}
        DOC "Google Breakpad library directory")

get_filename_component(_BREAKPAD_LIBRARY_DIR ${BREAKPAD_LIBRARY} PATH)
mark_as_advanced(BREAKPAD_LIBRARY)

set(BREAKPAD_LIBRARY_DIRS _BREAKPAD_CORE_LIBRARY_DIR _BREAKPAD_LIBRARY_DIR)
list(REMOVE_DUPLICATES BREAKPAD_LIBRARY_DIRS)
mark_as_advanced(BREAKPAD_LIBRARY_DIRS)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(breakpad
        REQUIRED_VARS BREAKPAD_INCLUDE_DIR BREAKPAD_LIBRARY
        VERSION_VAR BREAKPAD_VERSION_STRING)