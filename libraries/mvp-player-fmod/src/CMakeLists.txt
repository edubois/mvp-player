set(MVP_PLAYER_FMOD_SRC_PATH "${PROJECT_SOURCE_DIR}/src")
file(GLOB_RECURSE MVP_PLAYER_FMOD_SRC_FILES "*.cpp" "*.hpp" )

# Include mvpPlayerFMod and boost
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})

# Create 'mvpPlayerFMod' static lib
add_library(mvpPlayerFMod-static STATIC ${MVP_PLAYER_FMOD_SRC_FILES})
set_target_properties(mvpPlayerFMod-static PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(mvpPlayerFMod-static PROPERTIES OUTPUT_NAME mvpPlayerFMod)
target_link_libraries(mvpPlayerFMod-static ${Boost_LIBRARIES})

# Create 'mvpPlayerFMod' shared lib
add_library(mvpPlayerFMod-shared SHARED ${MVP_PLAYER_FMOD_SRC_FILES})
set_target_properties(mvpPlayerFMod-shared PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(mvpPlayerFMod-shared PROPERTIES OUTPUT_NAME mvpPlayerFMod)
set_target_properties(mvpPlayerFMod-shared PROPERTIES SOVERSION ${MVP_PLAYER_FMOD_VERSION_MAJOR})
set_target_properties(mvpPlayerFMod-shared PROPERTIES VERSION ${MVP_PLAYER_FMOD_VERSION})
target_link_libraries(mvpPlayerFMod-shared ${Boost_LIBRARIES})

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
