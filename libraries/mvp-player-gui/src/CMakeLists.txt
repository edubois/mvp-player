set(MVP_PLAYER_GUI_SRC_PATH "${PROJECT_SOURCE_DIR}/src")
file(GLOB_RECURSE MVP_PLAYER_GUI_SRC_FILES "*.cpp" "*.hpp" )

include(UseMvpPlayerBoost)

# Create 'mvpPlayerGui' static lib
add_library( mvpPlayerGui-static STATIC ${MVP_PLAYER_GUI_SRC_FILES} )
set_target_properties( mvpPlayerGui-static PROPERTIES LINKER_LANGUAGE CXX )
set_target_properties( mvpPlayerGui-static PROPERTIES OUTPUT_NAME mvpPlayerGui)
target_include_directories( mvpPlayerGui-static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_include_directories( mvpPlayerGui-static PUBLIC ${Boost_INCLUDE_DIRS} )
target_link_libraries( mvpPlayerGui-static ${Boost_LIBRARIES} mvpPlayerCore-static )

# Create 'mvpPlayerGui' shared lib
add_library( mvpPlayerGui-shared SHARED ${MVP_PLAYER_GUI_SRC_FILES} )
set_target_properties( mvpPlayerGui-shared PROPERTIES LINKER_LANGUAGE CXX )
set_target_properties( mvpPlayerGui-shared PROPERTIES OUTPUT_NAME mvpPlayerGui )
set_target_properties( mvpPlayerGui-shared PROPERTIES SOVERSION ${MVP_PLAYER_GUI_VERSION_MAJOR} )
set_target_properties( mvpPlayerGui-shared PROPERTIES VERSION ${MVP_PLAYER_GUI_VERSION} )
target_include_directories( mvpPlayerGui-shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_include_directories( mvpPlayerGui-shared PUBLIC ${Boost_INCLUDE_DIRS} )
target_link_libraries( mvpPlayerGui-shared ${Boost_LIBRARIES} mvpPlayerCore-shared )

### Install mvpPlayerGui libs and include
install(
	DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
	DESTINATION "include"
	FILES_MATCHING
	PATTERN "*.hpp"
	PATTERN "*.tcc"
)

install(TARGETS mvpPlayerGui-static DESTINATION lib/ OPTIONAL)
install(TARGETS mvpPlayerGui-shared DESTINATION lib/ OPTIONAL)
