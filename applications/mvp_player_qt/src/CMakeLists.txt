SET(BOOST_ADDS_SRC_PATH "${PROJECT_SOURCE_DIR}/src")

SET( MY_APP_NAME "MvpPlayer" )

# external modules
INCLUDE(BundleUtilities)
include(UseMvpPlayerBoost)

FILE( GLOB MVPPLAYER_SRCS *.cpp )

#--------------------------------------------------------------------------------
# For Apple set the icns file containing icons
IF(APPLE)
    # set how it shows up in the Info.plist file
    SET(MACOSX_BUNDLE_ICON_FILE "resources/${MY_APP_NAME}.icns")
    # set where in the bundle to put the icns file
    SET_SOURCE_FILES_PROPERTIES( ${CMAKE_CURRENT_SOURCE_DIR}/resources/${MY_APP_NAME}.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources )
    # include the icns file in the target
    SET( MVPPLAYER_SRCS ${MVPPLAYER_SRCS} "${CMAKE_CURRENT_SOURCE_DIR}/resources/${MY_APP_NAME}.icns" )

    # Locate all resourses
    FILE( GLOB COPY_RESOURCES "${CMAKE_CURRENT_SOURCE_DIR}/ui/buttons/*.ui" )
    SET_SOURCE_FILES_PROPERTIES(
      "${COPY_RESOURCES}"
      PROPERTIES
      MACOSX_PACKAGE_LOCATION Resources
    )

    SET( COPY_FRAMEWORKS  ${OGRE_FWK} ${OIS_FWK} )
    SET_SOURCE_FILES_PROPERTIES(
      ${COPY_FRAMEWORKS}
      PROPERTIES
      MACOSX_PACKAGE_LOCATION Frameworks
    )
ENDIF(APPLE)

add_executable( ${MY_APP_NAME} MACOSX_BUNDLE WIN32 ${MVPPLAYER_SRCS} ${COPY_RESOURCES} )
target_link_libraries( ${MY_APP_NAME} ${Boost_LIBRARIES} ${QT_LIBRARIES} ${BoostAdds_LIBRARIES} boostAdds-shared mvpPlayerCore-shared mvpPlayerNet-shared mvpPlayerFMod-shared mvpPlayerGui-shared mvpPlayerQtGui-shared )

# Install stuff
set( plugin_dest_dir bin )
set( qtconf_dest_dir bin )
set( APPS "\${CMAKE_INSTALL_PREFIX}/bin/${MY_APP_NAME}" )
if( APPLE )
    set( plugin_dest_dir ${MY_APP_NAME}.app/Contents/ )
    set( qtconf_dest_dir ${MY_APP_NAME}.app/Contents/Resources )
    set( APPS "\${CMAKE_INSTALL_PREFIX}/${MY_APP_NAME}.app" )
endif( APPLE )

if( WIN32 )
    set( APPS "\${CMAKE_INSTALL_PREFIX}/bin/${MY_APP_NAME}.exe" )
endif( WIN32 )

#--------------------------------------------------------------------------------
# This sets the windows build that will need the special winmain@16 call. Qt provides
#  this for us in the qtmain.lib file. Using this cmake code will ensure we have it
#  linked into our build. Not needed on Unix/OS X/Linux which is why we have the 
#  IF(WIN32) conditional.
IF (WIN32)
    SET (QT_USE_QTMAIN TRUE)
ENDIF (WIN32)


#--------------------------------------------------------------------------------
# Install the ${MY_APP_NAME} application, on Apple, the bundle is at the root of the
# install tree, and on other platforms it'll go into the bin directory.
INSTALL( TARGETS ${MY_APP_NAME}
    BUNDLE DESTINATION . COMPONENT Runtime
    RUNTIME DESTINATION bin COMPONENT Runtime
)

#--------------------------------------------------------------------------------
# Install needed Qt plugins by copying directories from the qt installation
# One can cull what gets copied by using 'REGEX "..." EXCLUDE'
install( DIRECTORY "${QT_PLUGINS_DIR}/imageformats"
    "${QT_PLUGINS_DIR}/codecs"
    "${QT_PLUGINS_DIR}/phonon_backend"
    "${QT_PLUGINS_DIR}/sqldrivers"
    "${QT_PLUGINS_DIR}/accessible"
    "${QT_PLUGINS_DIR}/bearer"
    "${QT_PLUGINS_DIR}/graphicssystems"
    DESTINATION ${plugin_dest_dir}/PlugIns
    COMPONENT Runtime
    FILES_MATCHING
    PATTERN "*.dylib"
    PATTERN "*_debug.dylib" EXCLUDE
)

IF(APPLE)
   # Add resources to application bundle target
   SET_TARGET_PROPERTIES(
     ${MY_APP_NAME}
     PROPERTIES
     RESOURCE "${COPY_RESOURCES}"
     )
ENDIF(APPLE)

#--------------------------------------------------------------------------------
# install a qt.conf file
# this inserts some cmake code into the install script to write the file
install( CODE "
    file(WRITE \"\${CMAKE_INSTALL_PREFIX}/${qtconf_dest_dir}/qt.conf\" \"\")
    " COMPONENT Runtime
)

# directories to look for dependencies
set( DIRS ${QT_LIBRARY_DIRS} ${BoostAdds_LIBRARIES} )

# Now the work of copying dependencies into the bundle/package
# The quotes are escaped and variables to use at install time have their $ escaped
# An alternative is the do a configure_file() on a script and use install(SCRIPT  ...).
# Note that the image plugins depend on QtSvg and QtXml, and it got those copied
# over.

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
install( CODE "
    file(GLOB_RECURSE QTPLUGINS
      \"\${CMAKE_INSTALL_PREFIX}/${plugin_dest_dir}/plugins/*${CMAKE_SHARED_LIBRARY_SUFFIX}\")
    set(BU_CHMOD_BUNDLE_ITEMS ON)
    include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\${QTPLUGINS}\" \"${DIRS}\")
    " COMPONENT Runtime
)

install(CODE "
    include(BundleUtilities)
    fixup_bundle(${CMAKE_INSTALL_PREFIX}/${MY_APP_NAME}.app \"\" \"\")
" COMPONENT Runtime)

# To Create a package, one can run "cpack -G DragNDrop CPackConfig.cmake" on Mac OS X
# where CPackConfig.cmake is created by including CPack
# And then there's ways to customize this as well
set( CPACK_BINARY_DRAGNDROP ON )
include( CPack )
