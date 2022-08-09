#!/usr/bin/env python3

import os

from .common_code import Common


class Headers(Common):

    def __init__(self,  sourcePath, moduleName, panelFileName, components):

        Common.__init__(self,  sourcePath, moduleName, panelFileName, components)

    def write(self):

        self._writePanelHeader()
        self._writeModuleHeader()

    def _addParamIds(self, line):

        counter = 0
        line(1, 'enum ParamId')
        line(1, '{')
        line(2, '// buttons')
        for button in self.buttons:
            name = button['name']
            line(2, f'{name} = {counter},')
            counter += 1
        line(2, '// switches')
        for switch in self.switches:
            name = switch['name']
            line(2, f'{name} = {counter},')
            counter += 1
        line(2, '// ledbuttons')
        for ledbutton in self.ledbuttons:
            name = ledbutton['name']
            line(2, f'{name} = {counter},')
            counter += 1
        line(2, '// knobs')
        for knob in self.knobs:
            name = knob['name']
            line(2, f'Knob_{name} = {counter},')
            counter += 1
        line(2, f'PARAMS_LEN = {counter}')
        line(1, '};')
        line(0)

    def _addDisplayIds(self, line):

        counter = 0
        line(1, 'enum DisplayId')
        line(1, '{')
        line(2, '// lcd')
        for lcd in self.lcds:
            name = lcd['name']
            line(2, f'Text_{name} = {counter},')
            counter += 1
        line(2, '// oled')
        for oled in self.oleds:
            name = oled['name']
            line(2, f'Pixels_{name} = {counter},')
            counter += 1
        line(2, f'DISPLAYS_LEN = {counter}')
        line(1, '};')
        line(0)

    def _addMeterIds(self, line):

        counter = 0
        line(1, 'enum MeterId')
        line(1, '{')
        for meter in self.meters:
            name = meter['name']
            line(2, f'Value_{name} = {counter},')
            counter += 1
        line(2, f'METERS_LEN = {counter}')
        line(1, '};')
        line(0)

    def _addInputIds(self, line):

        counter = 0
        line(1, 'enum InputId')
        line(1, '{')
        for input in self.inputs:
            name = input['name']
            line(2, f'{name} = {counter},')
            counter += 1
        line(2, f'INPUTS_LEN = {counter}')
        line(1, '};')
        line(0)

    def _addOutputIds(self, line):

        counter = 0
        line(1, 'enum OutputId')
        line(1, '{')
        for output in self.outputs:
            name = output['name']
            line(2, f'{name} = {counter},')
            counter += 1
        line(2, f'OUTPUTS_LEN = {counter}')
        line(1, '};')
        line(0)

    def _addLightIds(self, line):

        counter = 0
        line(1, 'enum LightId')
        line(1, '{')
        line(2, '// leds')
        for led in self.leds:
            name = led['name']
            line(2, f'RGB_{name} = {counter},')
            counter += 3
        line(2, '// ledbuttons')
        for ledbutton in self.ledbuttons:
            name = ledbutton['name']
            line(2, f'RGB_{name} = {counter},')
            counter += 3
        line(2, '// lcds')
        for lcd in self.lcds:
            name = lcd['name']
            line(2, f'RGB_{name} = {counter},')
            counter += 3
        line(2, f'LIGHTS_LEN = {counter}')
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
            if self.buttons:
                line(0, '#include <SchweineSystemButton.h>')
            if self.knobs:
                line(0, '#include <SchweineSystemKnob.h>')
            if self.lcds:
                line(0, '#include <SchweineSystemDisplayLCD.h>')
            if self.ledbuttons:
                line(0, '#include <SchweineSystemButtonLED.h>')
            if self.leds:
                line(0, '#include <SchweineSystemLED.h>')
            if self.meters:
                line(0, '#include <SchweineSystemLightMeter.h>')
            if self.oleds:
                line(0, '#include <SchweineSystemDisplayOLED.h>')
            if self.switches:
                line(0, '#include <SchweineSystemSwitch.h>')
            line(0)

            line(0, f'struct {self.moduleName}::Panel')
            line(0, '{')

            self._addParamIds(line)
            self._addDisplayIds(line)
            self._addMeterIds(line)
            self._addInputIds(line)
            self._addOutputIds(line)
            self._addLightIds(line)

            line(0, '};')

            line(0)
            line(0, f'#endif // NOT {self.moduleName}PanelH')

    def _writeModuleHeader(self):

        fileName = self.compileFileName('.h')

        if os.path.exists(fileName):
            print(f'header {self.moduleName}.h already exists')
            return

        with open(fileName, 'w') as headerfile:

            line = self._lineFunction(headerfile)

            line(0, f'#ifndef {self.moduleName}H')
            line(0, f'#define {self.moduleName}H')
            line(0)
            line(0, '#include <rack.hpp>')
            line(0, 'using namespace rack;')
            line(0)
            line(0, '#include <SchweineSystemModule.h>')
            line(0, '#include <SchweineSystemModuleWidget.h>')
            line(0)

            line(0, f'class {self.moduleName} : public SchweineSystem::Module')
            line(0, '{')
            line(0, 'public:')
            line(1, 'struct Panel;')
            line(0)
            line(0, 'public:')
            line(1, f'{self.moduleName}();')
            line(0)
            line(0, 'public:')
            line(1, 'void process(const ProcessArgs& args) override;')
            line(0)
            line(0, 'private:')
            line(1, 'void setup();')
            line(0, '};')

            line(0)
            line(0, '// widget')
            line(0)

            line(0, f'class {self.moduleName}Widget : public SchweineSystem::ModuleWidget')
            line(0, '{')
            line(0, 'public:')
            line(1, f'{self.moduleName}Widget({self.moduleName}* module);')
            line(0)
            line(0, 'private:')
            line(1, 'void setup();')
            line(0, '};')
            line(0)
            line(0, f'#endif // NOT {self.moduleName}H')
