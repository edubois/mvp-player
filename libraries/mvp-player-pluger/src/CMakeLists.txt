set( MVP_PLAYER_PLUGER_SRC_PATH "${PROJECT_SOURCE_DIR}/src/mvp-player-pluger" )
file( GLOB_RECURSE MVP_PLAYER_PLUGER_SRC_FILES "${MVP_PLAYER_PLUGER_SRC_PATH}/*.cpp" )

include(UseMvpPlayerBoost)

# Find the QtCore library
FIND_PACKAGE(Qt5 COMPONENTS Core)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Create 'mvpPlayerPluger' static lib
add_library( mvpPlayerPluger-static STATIC ${MVP_PLAYER_PLUGER_SRC_FILES} )
set_target_properties( mvpPlayerPluger-static PROPERTIES LINKER_LANGUAGE CXX )
set_target_properties( mvpPlayerPluger-static PROPERTIES OUTPUT_NAME mvpPlayerPluger )
target_include_directories( mvpPlayerPluger-static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_include_directories( mvpPlayerPluger-static PUBLIC ${Boost_INCLUDE_DIRS} )
target_include_directories( mvpPlayerPluger-static PUBLIC ${Qt5Core_INCLUDE_DIRS} )
target_link_libraries( mvpPlayerPluger-static ${Boost_LIBRARIES} Qt5::Core mvpPlayerCore-static mvpPlayerGui-static )

# Create 'mvpPlayerPluger' shared lib
add_library( mvpPlayerPluger-shared SHARED ${MVP_PLAYER_PLUGER_SRC_FILES} )
set_target_properties( mvpPlayerPluger-shared PROPERTIES LINKER_LANGUAGE CXX )
set_target_properties( mvpPlayerPluger-shared PROPERTIES OUTPUT_NAME mvpPlayerPluger )
set_target_properties( mvpPlayerPluger-shared PROPERTIES SOVERSION ${MVP_PLAYER_PLUGER_VERSION_MAJOR} )
set_target_properties( mvpPlayerPluger-shared PROPERTIES VERSION ${MVP_PLAYER_PLUGER_VERSION} )
target_include_directories( mvpPlayerPluger-shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_include_directories( mvpPlayerPluger-shared PUBLIC ${Boost_INCLUDE_DIRS} )
target_include_directories( mvpPlayerPluger-shared PUBLIC ${Qt5Core_INCLUDE_DIRS} )
target_link_libraries( mvpPlayerPluger-shared ${Boost_LIBRARIES} Qt5::Core mvpPlayerCore-shared mvpPlayerGui-shared )

#set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}" )
set( CMAKE_POSITION_INDEPENDENT_CODE ON )

### Install mvpPlayerPluger libs and include
install(
	DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
	DESTINATION "include"
	FILES_MATCHING
	PATTERN "*.hpp"
	PATTERN "*.tcc"
)

install( TARGETS mvpPlayerPluger-static DESTINATION lib/ OPTIONAL )
install( TARGETS mvpPlayerPluger-shared DESTINATION lib/ OPTIONAL )
