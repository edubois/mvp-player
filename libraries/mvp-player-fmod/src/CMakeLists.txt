set(MVP_PLAYER_FMOD_SRC_PATH "${PROJECT_SOURCE_DIR}/src")
file(GLOB_RECURSE MVP_PLAYER_FMOD_SRC_FILES "*.cpp" "*.hpp" )

# External libs
include(UseMvpPlayerBoost)
find_package(FMod)

# Create 'mvpPlayerFMod' static lib
add_library( mvpPlayerFMod-static STATIC ${MVP_PLAYER_FMOD_SRC_FILES} )
set_target_properties( mvpPlayerFMod-static PROPERTIES LINKER_LANGUAGE CXX )
set_target_properties( mvpPlayerFMod-static PROPERTIES OUTPUT_NAME mvpPlayerFMod )
target_include_directories( mvpPlayerCore-static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_include_directories( mvpPlayerCore-static PUBLIC ${FMOD_INCLUDE_DIRS} )
target_include_directories( mvpPlayerCore-static PUBLIC ${Boost_INCLUDE_DIRS} )
target_link_libraries( mvpPlayerFMod-static ${Boost_LIBRARIES} ${FMOD_LIBRARY} mvpPlayerCore-static )

# Create 'mvpPlayerFMod' shared lib
add_library( mvpPlayerFMod-shared SHARED ${MVP_PLAYER_FMOD_SRC_FILES} )
set_target_properties( mvpPlayerFMod-shared PROPERTIES LINKER_LANGUAGE CXX )
set_target_properties( mvpPlayerFMod-shared PROPERTIES OUTPUT_NAME mvpPlayerFMod )
set_target_properties( mvpPlayerFMod-shared PROPERTIES SOVERSION ${MVP_PLAYER_FMOD_VERSION_MAJOR} )
set_target_properties( mvpPlayerFMod-shared PROPERTIES VERSION ${MVP_PLAYER_FMOD_VERSION} )
target_include_directories( mvpPlayerCore-shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_include_directories( mvpPlayerCore-shared PUBLIC ${FMOD_INCLUDE_DIRS} )
target_include_directories( mvpPlayerCore-shared PUBLIC ${Boost_INCLUDE_DIRS} )
target_link_libraries( mvpPlayerFMod-shared ${Boost_LIBRARIES} ${FMOD_LIBRARY} mvpPlayerCore-shared )
SET_TARGET_PROPERTIES( mvpPlayerFMod-shared PROPERTIES MACOSX_BUNDLE TRUE )

### Install mvpPlayerFMod libs and include
install(
	DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
	DESTINATION "include"
	FILES_MATCHING
	PATTERN "*.hpp"
	PATTERN "*.tcc"
)

install(TARGETS mvpPlayerFMod-static DESTINATION lib/ OPTIONAL)
install(TARGETS mvpPlayerFMod-shared DESTINATION lib/ OPTIONAL)
