# Project mvp-player
include(CPack)
cmake_minimum_required (VERSION 2.8)
project (MvpPlayer)

# Add a variable for production
set(MVP_PLAYER_PRODUCTION TRUE CACHE BOOL "Fully optimized for production usage.")
if(MVP_PLAYER_PRODUCTION)
  add_definitions(-DMVP_PLAYER_PRODUCTION)
endif()

set( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" "${CMAKE_CURRENT_SOURCE_DIR}/cmake-internal-modules" )

# set Mac flags:
if(APPLE)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register -ftemplate-depth=256 -std=c++11 -stdlib=libc++ -isysroot/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk" )
set( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -stdlib=libc++ -Wl,-syslibroot,/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk" )
# set unix flags
elseif(UNIX)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register -ftemplate-depth=256 -std=c++11" )
set( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}" )
endif()

# The install rule does not depend on all, i.e. everything will not be built before installing
set( CMAKE_SKIP_INSTALL_ALL_DEPENDENCY TRUE )

# Create an alias for all plugins.
#add_custom_target(mvp_player_plugins)
# Include subdirs
add_subdirectory(libraries/boost-adds)
add_subdirectory(libraries/mvp-player-core)
add_subdirectory(libraries/mvp-player-fmod)
add_subdirectory(libraries/mvp-player-gui)
#add_subdirectory(libraries/mvp-player-ncursesgui)
#add_subdirectory(libraries/mvp-player-net)
#add_subdirectory(libraries/mvp-player-pluger)
#add_subdirectory(libraries/mvp-player-qtgui)
#add_subdirectory(plugins)
#add_subdirectory(applications)

# Add a target to generate API documentation with Doxygen
