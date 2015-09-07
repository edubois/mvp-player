cmake_minimum_required(VERSION 2.8.11)

project(RecorderPlugin CXX)

FIND_PACKAGE(Qt5 COMPONENTS Core )
set(CMAKE_AUTOMOC ON)

# Set sequenceParser versions
set(RECORDER_PLUGIN_VERSION_MAJOR "1")
set(RECORDER_PLUGIN_VERSION_MINOR "0")
set(RECORDER_PLUGIN_VERSION_MICRO "0")
set(RECORDER_PLUGIN_VERSION ${RECORDER_PLUGIN_VERSION_MAJOR}.${RECORDER_PLUGIN_VERSION_MINOR}.${RECORDER_PLUGIN_VERSION_MICRO})

# Define sequenceParser versions
add_definitions(-DRECORDER_PLUGIN_VERSION_MAJOR=${RECORDER_PLUGIN_VERSION_MAJOR})
add_definitions(-DRECORDER_PLUGIN_VERSION_MINOR=${RECORDER_PLUGIN_VERSION_MINOR})
add_definitions(-DRECORDER_PLUGIN_VERSION_MICRO=${RECORDER_PLUGIN_VERSION_MICRO})

# CPP flags on debug / release mode
if(MSVC)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
else()
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -fPIC -pg -g")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fPIC -O3")
endif()

ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_NO_DEBUG)
ADD_DEFINITIONS(-DQT_SHARED)

set(RECORDER_PLUGIN_SRC_PATH "${PROJECT_SOURCE_DIR}/src")
file(GLOB_RECURSE RECORDER_PLUGIN_SRC_FILES "*.cpp" )

# external dependency
include(UseMvpPlayerBoost)

# Create 'recorderPlugin' shared lib
add_library( recorderPlugin SHARED ${RECORDER_PLUGIN_SRC_FILES} )
set_target_properties( recorderPlugin PROPERTIES LINKER_LANGUAGE CXX )
set_target_properties( recorderPlugin PROPERTIES OUTPUT_NAME recorderPlugin )
target_include_directories( recorderPlugin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_include_directories( recorderPlugin PUBLIC ${Boost_INCLUDE_DIRS} )
target_include_directories( recorderPlugin PUBLIC ${FMOD_INCLUDE_DIRS} )
target_link_libraries( recorderPlugin ${Boost_LIBRARIES} ${BoostAdds_LIBRARIES} ${FMOD_LIBRARY} boostAdds-shared mvpPlayerPluger-shared mvpPlayerCore-shared )

### Install recorderPlugin libs and include
install(
	DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
	DESTINATION "include"
	FILES_MATCHING
	PATTERN "*.hpp"
	PATTERN "*.tcc"
)

install(TARGETS recorderPlugin DESTINATION mvpPlayerPlugins/ OPTIONAL)
