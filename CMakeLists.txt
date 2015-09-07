# Project mvp-player
include(CPack)
cmake_minimum_required (VERSION 2.8)
project (MvpPlayer)

# Add a variable for production
set(MVP_PLAYER_PRODUCTION TRUE CACHE BOOL "Fully optimized for production usage.")
if(MVP_PLAYER_PRODUCTION)
  add_definitions(-DMVP_PLAYER_PRODUCTION)
endif()

set( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" )

if(CMAKE_COMPILER_IS_GNUCXX)
    if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    endif()
endif()

if(APPLE)
    SET(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
    SET(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION "com.apple.compilers.llvm.clang.1_0")
    SET(CMAKE_MACOSX_RPATH 0)
endif()

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC -stdlib=libc++")

if(WIN32)
    add_definitions(-DUNICODE -D_UNICODE)
    set(TARGET_ARCHITECTURE "x86")
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
add_subdirectory(libraries/mvp-player-pluger)
add_subdirectory(libraries/mvp-player-qtgui)
#add_subdirectory(libraries/mvp-player-ncursesgui)
add_subdirectory(libraries/mvp-player-net)
add_subdirectory(plugins)
add_subdirectory(applications)

# Add a target to generate API documentation with Doxygen
