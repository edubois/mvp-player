find_path(FMOD_INCLUDE_DIR fmod.hpp)
find_library(FMOD_LIBRARY NAMES FMOD fmod PATH_SUFFIXES lib)

set(FMOD_INCLUDE_DIRS ${FMOD_INCLUDE_DIR})
set(FMOD_LIBRARIES ${FMOD_LIBRARY})
include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(FMOD FMOD_INCLUDE_DIR FMOD_LIBRARY)
mark_as_advanced(FMOD_INCLUDE_DIR FMOD_LIBRARY)
