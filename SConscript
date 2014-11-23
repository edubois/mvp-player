Import( 'project' )
Import( 'libs' )


mvpPlayerFlags = { 'LIBPATH': [project.inOutputLib()],
                'CCFLAGS': [project.CC['warning3'],project.CC['sharedobject'] ],
                'CXXFLAGS':[],
                'CPPDEFINES':[],
             }

if project.env['mode'] == 'production' :
	mvpPlayerFlags['CPPDEFINES'].append( 'FACTIZ_PRODUCTION' )
	if 'visibilityhidden' in project.CC:
		mvpPlayerFlags['SHCCFLAGS'] = [project.CC['visibilityhidden']]

# If your compiler as a flag to mark undefined flags as error in shared libraries
if 'sharedNoUndefined' in project.CC:
	mvpPlayerFlags['SHLINKFLAGS'] = [project.CC['sharedNoUndefined']]

SConscript( [
              'libraries/mvp-player-core/SConscript',
              'libraries/mvp-player-qtgui/SConscript',
            ]
            +
            project.scanFiles( ['applications', 'tests'], accept=['SConscript'] )
          )

