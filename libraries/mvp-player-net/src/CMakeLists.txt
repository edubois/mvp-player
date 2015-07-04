set(MVP_PLAYER_NET_SRC_PATH "${PROJECT_SOURCE_DIR}/src")
file(GLOB_RECURSE MVP_PLAYER_NET_SRC_FILES "*.cpp" "*.hpp" )

include(UseMvpPlayerBoost)

# Create 'mvpPlayerNet' static lib
add_library( mvpPlayerNet-static STATIC ${MVP_PLAYER_NET_SRC_FILES} )
set_target_properties( mvpPlayerNet-static PROPERTIES LINKER_LANGUAGE CXX )
set_target_properties( mvpPlayerNet-static PROPERTIES OUTPUT_NAME mvpPlayerNet)
target_include_directories( mvpPlayerNet-static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_include_directories( mvpPlayerNet-static PUBLIC ${Boost_INCLUDE_DIRS} )
target_link_libraries( mvpPlayerNet-static ${Boost_LIBRARIES} mvpPlayerCore-static )

# Create 'mvpPlayerNet' shared lib
add_library( mvpPlayerNet-shared SHARED ${MVP_PLAYER_NET_SRC_FILES} )
set_target_properties( mvpPlayerNet-shared PROPERTIES LINKER_LANGUAGE CXX )
set_target_properties( mvpPlayerNet-shared PROPERTIES OUTPUT_NAME mvpPlayerNet )
set_target_properties( mvpPlayerNet-shared PROPERTIES SOVERSION ${MVP_PLAYER_NET_VERSION_MAJOR} )
set_target_properties( mvpPlayerNet-shared PROPERTIES VERSION ${MVP_PLAYER_NET_VERSION} )
target_include_directories( mvpPlayerNet-shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_include_directories( mvpPlayerNet-shared PUBLIC ${Boost_INCLUDE_DIRS} )
target_link_libraries( mvpPlayerNet-shared ${Boost_LIBRARIES} mvpPlayerCore-shared )

### Install mvpPlayerNet libs and include
install(
	DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
	DESTINATION "include"
	FILES_MATCHING
	PATTERN "*.hpp"
	PATTERN "*.tcc"
)

install(TARGETS mvpPlayerNet-static DESTINATION lib/ OPTIONAL)
install(TARGETS mvpPlayerNet-shared DESTINATION lib/ OPTIONAL)
