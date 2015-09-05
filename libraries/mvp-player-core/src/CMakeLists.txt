set(MVP_PLAYER_CORE_SRC_PATH "${PROJECT_SOURCE_DIR}/src/mvp-player-core")
file(GLOB_RECURSE MVP_PLAYER_CORE_SRC_FILES "*.cpp" "*.hpp" )

# external dependency
include(UseMvpPlayerBoost)

# Create 'mvpPlayerCore' static lib
add_library( mvpPlayerCore-static STATIC ${MVP_PLAYER_CORE_SRC_FILES} )
set_target_properties( mvpPlayerCore-static PROPERTIES LINKER_LANGUAGE CXX )
set_target_properties( mvpPlayerCore-static PROPERTIES OUTPUT_NAME mvpPlayerCore )
target_include_directories( mvpPlayerCore-static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries( mvpPlayerCore-static ${Boost_LIBRARIES} ${BoostAdds_LIBRARIES} boostAdds-static )

# Create 'mvpPlayerCore' shared lib
add_library( mvpPlayerCore-shared SHARED ${MVP_PLAYER_CORE_SRC_FILES} )
set_target_properties( mvpPlayerCore-shared PROPERTIES LINKER_LANGUAGE CXX )
set_target_properties( mvpPlayerCore-shared PROPERTIES OUTPUT_NAME mvpPlayerCore )
set_target_properties( mvpPlayerCore-shared PROPERTIES SOVERSION ${MVP_PLAYER_CORE_VERSION_MAJOR} )
set_target_properties( mvpPlayerCore-shared PROPERTIES VERSION ${MVP_PLAYER_CORE_VERSION} )
target_include_directories( mvpPlayerCore-shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries( mvpPlayerCore-shared ${Boost_LIBRARIES} ${BoostAdds_LIBRARIES} boostAdds-shared )

### Install mvpPlayerCore libs and include
install(
	DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
	DESTINATION "include"
	FILES_MATCHING
	PATTERN "*.hpp"
	PATTERN "*.tcc"
)

if(APPLE)
    set_target_properties(mvpPlayerCore-shared
    PROPERTIES LINK_FLAGS "-framework CoreFoundation -w")
    set_target_properties(mvpPlayerCore-shared
    PROPERTIES INSTALL_RPATH "@loader_path")
endif(APPLE)

install(TARGETS mvpPlayerCore-static DESTINATION lib/ OPTIONAL)
install(TARGETS mvpPlayerCore-shared DESTINATION lib/ OPTIONAL)
