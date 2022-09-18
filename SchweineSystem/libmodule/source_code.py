#!/usr/bin/env python3

import os

from .common_code import Common


class Source(Common):

    def __init__(self, sourcePath, moduleName, panelFileName, components):

        Common.__init__(self, sourcePath, moduleName, panelFileName, components)

    def write(self):

        fileName = self.compileFileName('.cpp')

        if os.path.exists(fileName):
            print(f'source {self.moduleName}.cpp already exists')
            return

        with open(fileName, 'w') as sourcefile:

            line = self._lineFunction(sourcefile)

            line(0, f'#include "{self.moduleName}.h"')
            line(0)

            line(0, f'{self.moduleName}::{self.moduleName}()')
            line(1, ': Svin::Module()')
            line(0, '{')
            line(1, 'setup();')
            line(0, '}')
            line(0)

            line(0, f'void {self.moduleName}::process(const ProcessArgs& args)')
            line(0, '{')
            line(0, '}')
            line(0)

            line(0)
            line(0, '// widget')
            line(0)

            line(0, f'{self.moduleName}Widget::{self.moduleName}Widget({self.moduleName}* module)')
            line(0, f': Svin::ModuleWidget(module)')
            line(0, '{')
            line(1, 'setup();')
            line(0, '}')
            line(0)
