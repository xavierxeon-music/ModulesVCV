#!/usr/bin/env python3

import os

from .common_code import Common


class Headers(Common):

    def __init__(self, modulesPath, subFolder, moduleName, components):

        Common.__init__(self, modulesPath, subFolder, moduleName, components)

    def write(self):

        self._writePanelHeader()
        self._writeModuleHeader()

    def _addParamIds(self, line):

        line(1, 'enum ParamId')
        line(1, '{')
        for button in self.buttons:
            name = button['name']
            line(2, f'{name},')
        for display in self.displays:
            name = display['name']
            line(2, f'Value_{name},')
        for knob in self.knobs:
            name = knob['name']
            line(2, f'Knob_{name},')
        for meter in self.meters:
            name = meter['name']
            line(2, f'Value_{name},')
        line(2, 'PARAMS_LEN')
        line(1, '};')
        line(0)

    def _addInputIds(self, line):

        line(1, 'enum InputId')
        line(1, '{')
        for input in self.inputs:
            name = input['name']
            line(2, f'{name},')
        line(2, 'INPUTS_LEN')
        line(1, '};')
        line(0)

    def _addOutputIds(self, line):

        line(1, 'enum OutputId')
        line(1, '{')
        for output in self.outputs:
            name = output['name']
            line(2, f'{name},')
        line(2, 'OUTPUTS_LEN')
        line(1, '};')
        line(0)

    def _addLightIds(self, line):

        line(1, 'enum LightId')
        line(1, '{')
        for light in self.lights:
            name = light['name']
            line(2, f'Red_{name},')
            line(2, f'Green_{name},')
            line(2, f'Blue_{name},')
        for button in self.buttons:
            name = button['name']
            line(2, f'Red_{name},')
            line(2, f'Green_{name},')
            line(2, f'Blue_{name},')
        for display in self.displays:
            name = display['name']
            line(2, f'Red_{name},')
            line(2, f'Green_{name},')
            line(2, f'Blue_{name},')
        line(2, 'LIGHTS_LEN')
        line(1, '};')
        line(0)

    def _writePanelHeader(self):

        fileName = self.compileFileName('Panel.h')

        with open(fileName, 'w') as headerfile:

            line = self._lineFunction(headerfile)

            line(0, f'#ifndef {self.moduleName}PanelH')
            line(0, f'#define {self.moduleName}PanelH')
            line(0)
            line(0, f'#include "{self.moduleName}.h"')
            line(0)

            line(0, '#include <SchweineSystemCommon.h>')
            if self.displays:
                line(0, '#include <SchweineSystemLCDDisplay.h>')
            if self.lights:
                line(0, '#include <SchweineSystemLight.h>')
            if self.meters:
                line(0, '#include <SchweineSystemLightMeter.h>')
            line(0)

            line(0, f'struct {self.moduleName}::Panel')
            line(0, '{')

            self._addParamIds(line)
            self._addInputIds(line)
            self._addOutputIds(line)
            self._addLightIds(line)

            line(1, 'Panel();')
            line(0, '};')

            line(0)
            line(0, f'#endif // NOT {self.moduleName}PanelH')

    def _writeModuleHeader(self):

        fileName = self.compileFileName('.h')

        if os.path.exists(fileName):
            print(f'header {fileName} already exists')
            return

        with open(fileName, 'w') as headerfile:

            line = self._lineFunction(headerfile)

            line(0, f'#ifndef {self.moduleName}H')
            line(0, f'#define {self.moduleName}H')
            line(0)
            line(0, '#include <rack.hpp>')
            line(0, 'using namespace rack;')
            line(0)

            line(0, f'class {self.moduleName} : public Module')
            line(0, '{')
            line(0, 'public:')
            line(1, 'struct Panel;')
            line(0)
            line(0, 'public:')
            line(1, f'{self.moduleName}();')
            line(1, f'~{self.moduleName}();')
            line(0)
            line(0, 'public:')
            line(1, 'void process(const ProcessArgs& args) override;')
            line(0)
            line(0, 'private:')
            line(1, 'void setup();')
            line(0)
            line(0, 'private:')
            line(1, 'Panel* panel;')
            line(0, '};')

            line(0)

            line(0, f'class {self.moduleName}Widget : public ModuleWidget')
            line(0, '{')
            line(0, 'public:')
            line(1, f'{self.moduleName}Widget({self.moduleName}* module);')
            line(0)
            line(0, 'private:')
            line(1, f'SvgPanel* setup({self.moduleName}* module);')
            line(0, '};')
            line(0)
            line(0, f'#endif // NOT {self.moduleName}H')
