#.rst:
# FindAVIF
# --------
# Finds the avif library
#
# This will will define the following variables::
#
# AVIF_FOUND - system has libavif
# AVIF_INCLUDE_DIRS - the aom include directory
# AVIF_LIBRARIES - the aom libraries
#
# and the following imported targets::
#
#   AVIF::AVIF- The AVIF library

if(PKG_CONFIG_FOUND)
  pkg_check_modules(PC_AVIF avif QUIET)
endif()

find_path(AVIF_INCLUDE_DIR NAMES avif/avif.h
          PATHS ${PC_AVIF_INCLUDEDIR})
find_library(AVIF_LIBRARY NAMES avif libavif
             PATHS ${PC_AVIF_LIBDIR})

           set(AVIF_VERSION ${PC_AVIF_VERSION})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(AVIF
                                  REQUIRED_VARS AVIF_LIBRARY AVIF_INCLUDE_DIR
                                  VERSION_VAR AVIF_VERSION)

if(AVIF_FOUND)
  set(AVIF_LIBRARIES ${AVIF_LIBRARY})

  if(NOT TARGET AVIF::AVIF)
    add_library(AVIF::AVIF UNKNOWN IMPORTED)
    set_target_properties(AVIF::AVIF PROPERTIES
                          IMPORTED_LOCATION "${AVIF_LIBRARY}")
  endif()
endif()

mark_as_advanced(AVIF_INCLUDE_DIR AVIF_LIBRARY)
