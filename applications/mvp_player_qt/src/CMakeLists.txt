set(BOOST_ADDS_SRC_PATH "${PROJECT_SOURCE_DIR}/src")
file(GLOB_RECURSE BOOST_ADDS_SRC_FILES "*.cpp" )

# external libs
include(UseMvpPlayerBoost)

add_executable( mvpPlayerQt-static main.cpp )
target_link_libraries( mvpPlayerQt-static ${Boost_LIBRARIES} ${BoostAdds_LIBRARIES} boostAdds-static mvpPlayerCore-static mvpPlayerNet-static mvpPlayerFMod-static mvpPlayerGui-static mvpPlayerQtGui-static )

add_executable( mvpPlayerQt-shared main.cpp )
target_link_libraries( mvpPlayerQt-shared ${Boost_LIBRARIES} ${BoostAdds_LIBRARIES} boostAdds-shared mvpPlayerCore-shared mvpPlayerNet-shared mvpPlayerFMod-shared mvpPlayerGui-shared mvpPlayerQtGui-shared )

### Install boostAdds libs and include
install(
	DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
	DESTINATION "include"
	FILES_MATCHING
	PATTERN "*.hpp"
	PATTERN "*.tcc"
)

install(TARGETS mvpPlayerQt-static DESTINATION bin/ OPTIONAL)
