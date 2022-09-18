#!/usr/bin/env python3

import os

from .common_code import Common


class Panel(Common):

    def __init__(self,  sourcePath, moduleName, panelFileName, components):

        Common.__init__(self,  sourcePath, moduleName, panelFileName, components)

    def write(self):

        fileName = self.compileFileName('.hpp')

        with open(fileName, 'w') as headerfile:

            line = self._lineFunction(headerfile)

            line(0, f'#ifndef {self.moduleName}HPP')
            line(0, f'#define {self.moduleName}HPP')
            line(0)
            line(0, f'#include "{self.moduleName}.h"')
            line(0)
            line(0, '#include <SvinOrigin.h>')
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

            self._addModuleSetup(line)
            line(0)

            self._addWidgetSetup(line)
            line(0)

            line(0, f'Model* model{self.moduleName} = Svin::Origin::the()->addModule<{self.moduleName}, {self.moduleName}Widget>("{self.moduleName}");')
            line(0)

            line(0, f'#endif // NOT {self.moduleName}HPP')

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
            line(2, f'{name} = {counter},')
            counter += 1
        line(2, '// sliders')
        for slider in self.sliders:
            name = slider['name']
            line(2, f'{name} = {counter},')
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
        line(2, '// sliders')
        for slider in self.sliders:
            name = slider['name']
            line(2, f'RGB_{name} = {counter},')
            counter += 3
        line(2, f'LIGHTS_LEN = {counter}')
        line(1, '};')
        line(0)

    def _addModuleSetup(self, line):

        line(0, f'void {self.moduleName}::setup()')
        line(0, '{')
        line(1, 'config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);')

        if self.buttons:
            line(0)
        for button in self.buttons:
            name = button['name']
            line(1, f'configButton(Panel::{name}, "{name}");')

        if self.sliders:
            line(0)
        for slider in self.sliders:
            name = slider['name']
            line(1, f'configSwitch(Panel::{name}, 0.0f, 1.0f, 0.0f, "{name}");')

        if self.switches:
            line(0)
        for switch in self.switches:
            name = switch['name']
            line(1, f'configSwitch(Panel::{name}, 0.0f, 1.0f, 0.0f, "{name}");')

        if self.ledbuttons:
            line(0)
        for ledbutton in self.ledbuttons:
            name = ledbutton['name']
            line(1, f'configButton(Panel::{name}, "{name}");')

        if self.knobs:
            line(0)
        for knob in self.knobs:
            name = knob['name']
            line(1, f'configParam(Panel::{name}, -1.f, 1.f, 0.f, "{name}");')

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

        line(0, '}')

    def _addWidgetSetup(self, line):

        line(0, f'void {self.moduleName}Widget::setup()')
        line(0, '{')
        line(1, f'std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "{self.panelFileName}");')
        line(1, 'SvgPanel* mainPanel = createPanel(panelPath);')
        line(1, 'setPanel(mainPanel);')

        if self.buttons:
            line(0)
        for button in self.buttons:
            name = button['name']
            x = button['cx']
            y = button['cy']
            line(1, f'makeButton(this, Vec({x:.2f}, {y:.2f}), {self.moduleName}::Panel::{name});')

        if self.sliders:
            line(0)
        for slider in self.sliders:
            name = slider['name']
            x = slider['cx']
            y = slider['cy']
            line(1, f'makeSlider(this, Vec({x:.2f}, {y:.2f}), {self.moduleName}::Panel::{name}, {self.moduleName}::Panel::RGB_{name});')

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
            line(1, f'makeKnob(this, Vec({x:.2f}, {y:.2f}), {self.moduleName}::Panel::{name}, {size});')

        if self.inputs:
            line(0)
        for input in self.inputs:
            name = input['name']
            x = input['cx']
            y = input['cy']
            poly = 'true' if input['count'] != 1 else 'false'
            line(1, f'makeInput(this, Vec({x:.2f}, {y:.2f}),  {self.moduleName}::Panel::{name}, {poly});')

        if self.outputs:
            line(0)
        for output in self.outputs:
            name = output['name']
            x = output['cx']
            y = output['cy']
            poly = 'true' if output['count'] != 1 else 'false'
            line(1, f'makeOutput(this, Vec({x:.2f}, {y:.2f}), {self.moduleName}::Panel::{name}, {poly});')

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
            fontSize = 18
            line(1, f'makeLCD(this, Vec({x:.2f}, {y:.2f}), {count}, {self.moduleName}::Panel::Text_{name}, {fontSize});')

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
