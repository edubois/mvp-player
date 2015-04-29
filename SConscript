Import( 'project' )
Import( 'libs' )


mvpPlayerFlags = { 'LIBPATH': [project.inOutputLib()],
                'CCFLAGS': [project.CC['warning3'],project.CC['sharedobject'] ],
                'CXXFLAGS':[],
                'CPPDEFINES':['BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS', 'BOOST_MPL_LIMIT_LIST_SIZE=30'],
             }

if project.env['mode'] == 'production' :
	mvpPlayerFlags['CPPDEFINES'].append( 'FACTIZ_PRODUCTION' )
	if 'visibilityhidden' in project.CC:
		mvpPlayerFlags['SHCCFLAGS'] = [project.CC['visibilityhidden']]

# If your compiler as a flag to mark undefined flags as error in shared libraries
if 'sharedNoUndefined' in project.CC:
	mvpPlayerFlags['SHLINKFLAGS'] = [project.CC['sharedNoUndefined']]


mvpPlayer = project.ObjectLibrary( 'mvpPlayer',
                                   envFlags=mvpPlayerFlags )

project.commonLibs.append( mvpPlayer )


SConscript( [
              'libraries/boost-adds/SConscript',
              'libraries/mvp-player-core/SConscript',
              'libraries/mvp-player-gui/SConscript',
              'libraries/mvp-player-net/SConscript',
              'libraries/mvp-player-pluger/SConscript',
              'libraries/mvp-player-qtgui/SConscript',
              'libraries/mvp-player-ncursesgui/SConscript',
            ]
            +
            project.scanFiles( ['plugins', 'applications', 'tests'], accept=['SConscript'] )
          )

