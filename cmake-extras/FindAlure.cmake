# - Try to find Alure
# Once done, this will define
# ALURE_FOUND - system has Alure
# ALURE_INCLUDE_DIRS - the Alure Include directories
# ALURE_LIBRARIES - link these to use Alure

# find the Alure include directory
find_path(ALURE_INCLUDE_DIR
    NAMES
        alure.h
    PATH_SUFFIXES
        AL OpenAL
    PATHS
        /usr/include
        /usr/local/include
        /opt/local/include
        /sw/include
        ${ALURE_DIR}/src/
)

# find the Alure library
find_library(ALURE_LIBRARY
    NAMES
        alure
    PATH_SUFFIXES
        lib64 lib
    PATHS
        /usr
        /usr/local
        /opt/local
        /sw
        ${ALURE_DIR}/lib
)

# handle the QUIETLY and REQUIRED arguments and set ALURE_FOUND to TRUE if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ALURE DEFAULT_MSG ALURE_INCLUDE_DIR ALURE_LIBRARY)
mark_as_advanced(ALURE_INCLUDE_DIR ALURE_LIBRARY)