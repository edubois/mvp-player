cmake_minimum_required(VERSION 2.8.11)

project(MvpPlayerQtGui CXX)

# Set sequenceParser versions
set(MVP_PLAYER_QTGUI_VERSION_MAJOR "1")
set(MVP_PLAYER_QTGUI_VERSION_MINOR "0")
set(MVP_PLAYER_QTGUI_VERSION_MICRO "0")
set(MVP_PLAYER_QTGUI_VERSION ${MVP_PLAYER_QTGUI_VERSION_MAJOR}.${MVP_PLAYER_QTGUI_VERSION_MINOR}.${MVP_PLAYER_QTGUI_VERSION_MICRO})

# Define sequenceParser versions
add_definitions(-DMVP_PLAYER_QTGUI_VERSION_MAJOR=${MVP_PLAYER_QTGUI_VERSION_MAJOR})
add_definitions(-DMVP_PLAYER_QTGUI_VERSION_MINOR=${MVP_PLAYER_QTGUI_VERSION_MINOR})
add_definitions(-DMVP_PLAYER_QTGUI_VERSION_MICRO=${MVP_PLAYER_QTGUI_VERSION_MICRO})

# The install rule does not depend on all, i.e. everything will not be built before installing
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY TRUE)

# CPP flags on debug / release mode
if(MSVC)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
else()
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -fPIC -frtti -pg -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fPIC -frtti -O3")
endif()

add_subdirectory(src)
