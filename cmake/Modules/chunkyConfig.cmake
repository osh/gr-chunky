INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_CHUNKY chunky)

FIND_PATH(
    CHUNKY_INCLUDE_DIRS
    NAMES chunky/api.h
    HINTS $ENV{CHUNKY_DIR}/include
        ${PC_CHUNKY_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    CHUNKY_LIBRARIES
    NAMES gnuradio-chunky
    HINTS $ENV{CHUNKY_DIR}/lib
        ${PC_CHUNKY_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CHUNKY DEFAULT_MSG CHUNKY_LIBRARIES CHUNKY_INCLUDE_DIRS)
MARK_AS_ADVANCED(CHUNKY_LIBRARIES CHUNKY_INCLUDE_DIRS)

