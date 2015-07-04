set(MVP_PLAYER_QTGUI_SRC_PATH "${PROJECT_SOURCE_DIR}/src")
file(GLOB_RECURSE MVP_PLAYER_QTGUI_SRC_FILES "*.cpp" "*.hpp" )

include(UseMvpPlayerBoost)

# Find the QtWidgets library
FIND_PACKAGE(Qt5 COMPONENTS Core Gui Widgets)
SET(CMAKE_AUTOMOC ON)

# Create 'mvpPlayerQtGui' static lib
add_library( mvpPlayerQtGui-static STATIC ${MVP_PLAYER_QTGUI_SRC_FILES} )
set_target_properties( mvpPlayerQtGui-static PROPERTIES LINKER_LANGUAGE CXX )
set_target_properties( mvpPlayerQtGui-static PROPERTIES OUTPUT_NAME mvpPlayerQtGui )
target_include_directories( mvpPlayerQtGui-static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_include_directories( mvpPlayerQtGui-static PUBLIC ${Boost_INCLUDE_DIRS} )
target_link_libraries( mvpPlayerQtGui-static ${Boost_LIBRARIES} mvpPlayerPluger-static mvpPlayerGui-static Qt5::Core Qt5::Gui Qt5::Widgets )

# Create 'mvpPlayerQtGui' shared lib
add_library( mvpPlayerQtGui-shared SHARED ${MVP_PLAYER_QTGUI_SRC_FILES} )
set_target_properties( mvpPlayerQtGui-shared PROPERTIES LINKER_LANGUAGE CXX )
set_target_properties( mvpPlayerQtGui-shared PROPERTIES OUTPUT_NAME mvpPlayerQtGui )
set_target_properties( mvpPlayerQtGui-shared PROPERTIES SOVERSION ${MVP_PLAYER_QTGUI_VERSION_MAJOR} )
set_target_properties( mvpPlayerQtGui-shared PROPERTIES VERSION ${MVP_PLAYER_QTGUI_VERSION} )
target_include_directories( mvpPlayerQtGui-shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_include_directories( mvpPlayerQtGui-shared PUBLIC ${Boost_INCLUDE_DIRS} )
target_link_libraries( mvpPlayerQtGui-shared ${Boost_LIBRARIES} mvpPlayerPluger-shared mvpPlayerGui-shared Qt5::Core Qt5::Gui Qt5::Widgets )

### Install mvpPlayerQtGui libs and include
install(
	DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
	DESTINATION "include"
	FILES_MATCHING
	PATTERN "*.hpp"
	PATTERN "*.tcc"
)

install(TARGETS mvpPlayerQtGui-static DESTINATION lib/ OPTIONAL)
install(TARGETS mvpPlayerQtGui-shared DESTINATION lib/ OPTIONAL)
