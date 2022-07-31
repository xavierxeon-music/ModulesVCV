#!/usr/bin/env python3

import os

from .common_code import Common


class Sources(Common):

    def __init__(self, modulesPath, subFolder, moduleName, components):

        Common.__init__(self, modulesPath, subFolder, moduleName, components)

    def write(self):

        self._writePanelSource()
        self._writeModuleSource()

    def _addModuleSetup(self, line):

        line(0, f'void {self.moduleName}::setup()')
        line(0, '{')
        line(1, 'config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);')

        if self.buttons:
            line(0)
        for button in self.buttons:
            name = button['name']
            line(1, f'configButton(Panel::{name}, "{name}");')

        if self.switches:
            line(0)
        for switch in self.switches:
            name = switch['name']
            line(1, f'configSwitch(Panel::{name}, 0.0f, 1.0f, 0.0f, "{name}");')

        if self.ledbuttons:
            line(0)
        for ledbutton in self.ledbuttons:
            name = ledbutton['name']
            x = ledbutton['cx']
            y = ledbutton['cy']
            line(1, f'configButton(Panel::{name}, "{name}");')

        if self.knobs:
            line(0)
        for knob in self.knobs:
            name = knob['name']
            line(1, f'configParam(Panel::Knob_{name}, -1.f, 1.f, 0.f, "");')

        if self.inputs:
            line(0)
        for input in self.inputs:
            name = input['name']
            line(1, f'configInput(Panel::{name}, "{name}");')

        if self.outputs:
            line(0)
        for output in self.outputs:
            name = output['name']
            line(1, f'configOutput(Panel::{name}, "{name}");')

        if self.lcds:
            line(0)
        for lcd in self.lcds:
            name = lcd['name']
            line(1, f'configText(Panel::Text_{name}, "{name}");')

        if self.oleds:
            line(0)
        for oled in self.oleds:
            name = oled['name']
            count = oled['count']
            width, height = count.split('x')
            line(1, f'configPixels(Panel::Pixels_{name}, {width}, {height}, "{name}");')

        if self.meters:
            line(0)
        for meter in self.meters:
            name = meter['name']
            line(1, f'configMeter(Panel::Value_{name}, "{name}");')

        line(0, '}')

    def _addWidgetSetup(self, line):

        line(0, f'void {self.moduleName}Widget::setup()')
        line(0, '{')
        if self.subFolder:
            line(1, f'std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/{self.subFolder}/{self.moduleName}.svg");')
        else:
            line(1, f'std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/{self.moduleName}.svg");')
        line(1, 'SvgPanel* mainPanel = createPanel(panelPath);')
        line(1, 'setPanel(mainPanel);')

        if self.buttons:
            line(0)
        for button in self.buttons:
            name = button['name']
            x = button['cx']
            y = button['cy']
            line(1, f'makeButton(this, Vec({x:.2f}, {y:.2f}), {self.moduleName}::Panel::{name});')

        if self.switches:
            line(0)
        for switch in self.switches:
            name = switch['name']
            x = switch['cx']
            y = switch['cy']
            line(1, f'makeSwitch(this, Vec({x:.2f}, {y:.2f}), {self.moduleName}::Panel::{name});')

        if self.ledbuttons:
            line(0)
        for ledbutton in self.ledbuttons:
            name = ledbutton['name']
            x = ledbutton['cx']
            y = ledbutton['cy']
            line(1, f'makeLEDButton(this, Vec({x:.2f}, {y:.2f}), {self.moduleName}::Panel::{name}, {self.moduleName}::Panel::RGB_{name});')

        if self.knobs:
            line(0)
        for knob in self.knobs:
            name = knob['name']
            x = knob['cx']
            y = knob['cy']
            size = knob['count']
            line(1, f'makeKnob(this, Vec({x:.2f}, {y:.2f}), {self.moduleName}::Panel::Knob_{name}, {size});')

        if self.inputs:
            line(0)
        for input in self.inputs:
            name = input['name']
            x = input['cx']
            y = input['cy']
            line(1, f'makeInput(this, Vec({x:.2f}, {y:.2f}),  {self.moduleName}::Panel::{name});')

        if self.outputs:
            line(0)
        for output in self.outputs:
            name = output['name']
            x = output['cx']
            y = output['cy']
            line(1, f'makeOutput(this, Vec({x:.2f}, {y:.2f}), {self.moduleName}::Panel::{name});')

        if self.leds:
            line(0)
        for led in self.leds:
            name = led['name']
            x = led['cx']
            y = led['cy']
            line(1, f'makeLED(this, Vec({x:.2f}, {y:.2f}), {self.moduleName}::Panel::RGB_{name});')

        if self.lcds:
            line(0)
        for lcd in self.lcds:
            name = lcd['name']
            count = lcd['count']
            x = lcd['rx']
            y = lcd['ry']
            line(1, f'makeLCD(this, Vec({x:.2f}, {y:.2f}), {count}, {self.moduleName}::Panel::Text_{name}, {self.moduleName}::Panel::RGB_{name});')

        if self.oleds:
            line(0)
        for oled in self.oleds:
            name = oled['name']
            x = oled['rx']
            y = oled['ry']
            count = oled['count']
            width, height = count.split('x')
            line(1, f'makeOLED(this, Vec({x:.2f}, {y:.2f}), {self.moduleName}::Panel::Pixels_{name}, {width}, {height});')

        if self.meters:
            line(0)
        for meter in self.meters:
            name = meter['name']
            count = meter['count']
            x = meter['rx']
            y = meter['ry']
            line(1, f'makeMeter(this, Vec({x:.2f}, {y:.2f}), {count}, {self.moduleName}::Panel::Value_{name});')

        line(0, '}')

    def _writePanelSource(self):

        fileName = self.compileFileName('Panel.cpp')

        with open(fileName, 'w') as sourcefile:

            line = self._lineFunction(sourcefile)

            line(0, f'#include "{self.moduleName}.h"')
            line(0, f'#include "{self.moduleName}Panel.h"')
            line(0)
            line(0, '#include <SchweineSystemMaster.h>')
            if self.lcds:
                line(0, '#include <limits>')
            line(0)

            self._addModuleSetup(line)
            line(0)

            self._addWidgetSetup(line)
            line(0)

    def _writeModuleSource(self):

        fileName = self.compileFileName('.cpp')

        if os.path.exists(fileName):
            print(f'source {self.moduleName}.cpp already exists')
            return

        with open(fileName, 'w') as sourcefile:

            line = self._lineFunction(sourcefile)

            line(0, f'#include "{self.moduleName}.h"')
            line(0, f'#include "{self.moduleName}Panel.h"')
            line(0)
            line(0, '#include <SchweineSystemMaster.h>')
            line(0)

            line(0, f'{self.moduleName}::{self.moduleName}()')
            line(1, ': SchweineSystem::Module()')
            line(0, '{')
            line(1, 'setup();')
            line(0, '}')

            line(0, f'void {self.moduleName}::process(const ProcessArgs& args)')
            line(0, '{')
            line(0, '}')
            line(0)

            line(0)
            line(0, '// widget')
            line(0)

            line(0, f'{self.moduleName}Widget::{self.moduleName}Widget({self.moduleName}* module)')
            line(0, f': SchweineSystem::ModuleWidget(module)')
            line(0, '{')
            line(1, 'setup();')
            line(0, '}')
            line(0)

            line(0, f'Model* model{self.moduleName} = SchweineSystem::Master::the()->addModule<{self.moduleName}, {self.moduleName}Widget>("{self.moduleName}");')
