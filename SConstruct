EnsureSConsVersion( 1, 2 )
EnsurePythonVersion( 2, 5 )

import os
import sys

sys.path.append('tools')
from sconsProject import SConsProject

class MVPPlayerMatchProject( SConsProject ):
    pass

#______________________________________________________________________________#

project = MVPPlayerMatchProject()

project.libs.qt_default = project.libs.qt5

Export('project')
Export({'libs':project.libs})

#______________________________________________________________________________#

project.begin()
project.SConscript()
project.end()



