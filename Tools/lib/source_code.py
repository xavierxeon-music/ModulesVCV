#!/usr/bin/env python3

import os

from .common_code import Common


class Sources(Common):

    def __init__(self, modulesPath, subFolder, moduleName, components):

        Common.__init__(self, modulesPath, subFolder, moduleName, components)

    def write(self):

        self._writePanelSource()
        self._writeModuleSource()

    def _writePanelSource(self):

        fileName = self.compileFileName('Panel.cpp')

        with open(fileName, 'w') as sourcefile:

            line = self._lineFunction(sourcefile)

    def _writeModuleSource(self):

        fileName = self.compileFileName('.cpp')

        if os.path.exists(fileName):
            print(f'source {fileName} already exists')
            return

        with open(fileName, 'w') as sourcefile:

            line = self._lineFunction(sourcefile)

            line(0, f'#include "{self.moduleName}.h"')
            line(0, f'#include "{self.moduleName}Panel.h"')
            line(0)
            line(0, '#include <SchweineSystemMaster.h>')
            line(0)

            line(0, f'{self.moduleName}::{self.moduleName}()')
            line(1, ': Module()')
            line(1, ', panel(nullptr)')
            line(0, '{')
            line(1, 'panel = new Panel();')
            line(1, 'setup();')
            line(0, '}')

            line(0)

            line(0, f'{self.moduleName}::~{self.moduleName}()')
            line(0, '{')
            line(1, 'delete panel;')
            line(0, '}')

            line(0)

            line(0, f'void {self.moduleName}::process(const ProcessArgs& args)')
            line(0, '{')
            line(0, '}')
            line(0)

            line(0, f'{self.moduleName}Widget::{self.moduleName}Widget({self.moduleName}* module)')
            line(0, f': ModuleWidget()')
            line(0, '{')
            line(1, 'SvgPanel* mainPanel = setup(module);')
            line(1, '(void)mainPanel;')
            line(0, '}')
            line(0)

            line(0, f'Model* model{self.moduleName} = SchweineSystem::Master::the()->addModule<{self.moduleName}, {self.moduleName}Widget>("{self.moduleName}");')
