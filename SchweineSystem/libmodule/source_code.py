#!/usr/bin/env python3

import os

from .common_code import Common


class Source(Common):

    def __init__(self, sourcePath, moduleName, panelFileName, components, metaMap):

        Common.__init__(self, sourcePath, moduleName, panelFileName, components, metaMap)

    def write(self):

        fileName = self.compileFileName('.cpp')

        if os.path.exists(fileName):
            print(f'source {self.moduleName}.cpp already exists')
            return

        with open(fileName, 'w') as sourcefile:

            line = self._lineFunction(sourcefile)

            className = self.moduleName
            fullClassName = self.moduleName
            if self.namespace:
                className = className.replace(self.namespace, '')
                fullClassName = fullClassName.replace(self.namespace, self.namespace + '::')

            line(0, f'#include "{self.moduleName}.h"')
            line(0)

            line(0, f'{fullClassName}::{className}()')
            line(1, ': Svin::Module()')
            line(0, '{')
            line(1, 'setup();')
            line(0, '}')
            line(0)

            line(0, f'void {fullClassName}::process(const ProcessArgs& args)')
            line(0, '{')
            line(0, '}')
            line(0)

            line(0)
            line(0, '// widget')
            line(0)

            line(0, f'{fullClassName}Widget::{className}Widget({className}* module)')
            line(0, f': Svin::ModuleWidget(module)')
            line(0, '{')
            line(1, 'setup();')
            line(0, '}')
            line(0)

            line(0, '// create module')
            line(0, f'Model* model{self.moduleName} = Svin::Origin::the()->addModule<{fullClassName}, {fullClassName}Widget>("{self.moduleName}");')
            line(0)
