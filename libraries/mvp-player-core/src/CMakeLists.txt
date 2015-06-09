set(MVP_PLAYER_CORE_SRC_PATH "${PROJECT_SOURCE_DIR}/src")
file(GLOB_RECURSE MVP_PLAYER_CORE_SRC_FILES "*.cpp" "*.hpp" )

# Include mvpPlayerCore and boost
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})

# Create 'mvpPlayerCore' static lib
add_library(mvpPlayerCore-static STATIC ${MVP_PLAYER_CORE_SRC_FILES})
set_target_properties(mvpPlayerCore-static PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(mvpPlayerCore-static PROPERTIES OUTPUT_NAME mvpPlayerCore)
target_link_libraries(mvpPlayerCore-static ${Boost_LIBRARIES})

# Create 'mvpPlayerCore' shared lib
add_library(mvpPlayerCore-shared SHARED ${MVP_PLAYER_CORE_SRC_FILES})
set_target_properties(mvpPlayerCore-shared PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(mvpPlayerCore-shared PROPERTIES OUTPUT_NAME mvpPlayerCore)
set_target_properties(mvpPlayerCore-shared PROPERTIES SOVERSION ${MVP_PLAYER_CORE_VERSION_MAJOR})
set_target_properties(mvpPlayerCore-shared PROPERTIES VERSION ${MVP_PLAYER_CORE_VERSION})
target_link_libraries(mvpPlayerCore-shared ${Boost_LIBRARIES})

### Install mvpPlayerCore libs and include
install(
	DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
	DESTINATION "include"
	FILES_MATCHING
	PATTERN "*.hpp"
	PATTERN "*.tcc"
)

install(TARGETS mvpPlayerCore-static DESTINATION lib/ OPTIONAL)
install(TARGETS mvpPlayerCore-shared DESTINATION lib/ OPTIONAL)
