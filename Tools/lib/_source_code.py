#!/usr/bin/env python3

import os


def _indent(self, level):

    return ' ' * (3 * level)


def _writePanelSource(modulesPath, subFolder, panelName, components):

    if subFolder:
        fileName = modulesPath + '/src/' + subFolder + '/' + panelName + 'Panel.cpp'
    else:
        fileName = modulesPath + '/src/' + panelName + 'Panel.cpp'

    buttons = components['button'] if components and 'button' in components else list()
    displays = components['display'] if components and 'display' in components else list()
    inputs = components['input'] if components and 'input' in components else list()
    knobs = components['knob'] if components and 'knob' in components else list()
    lights = components['light'] if components and 'light' in components else list()
    meters = components['meter'] if components and 'meter' in components else list()
    outputs = components['output'] if components and 'output' in components else list()

    with open(fileName, 'w') as sourcefile:
        sourcefile.write(f'#include "{panelName}.h"\n')
        sourcefile.write(f'#include "{panelName}Panel.h"\n')
        sourcefile.write('\n')
        sourcefile.write('#include <SchweineSystemMaster.h>\n')
        if displays:
            sourcefile.write('#include <SchweineSystemLCDDisplay.h>\n')
            sourcefile.write('#include <limits>\n')
        sourcefile.write('\n')

        sourcefile.write(f'void {panelName}::setup()\n')
        sourcefile.write('{\n')
        sourcefile.write(_indent(1) + 'config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);\n')

        if displays:
            sourcefile.write('\n')
        for display in displays:
            name = display['name']
            count = int(display['count'])
            sourcefile.write(_indent(1) + f'configParam(Panel::Value_{name}, 0.f, {10**count}, 0.f, "");\n')

        if buttons:
            sourcefile.write('\n')
        for button in buttons:
            name = button['name']
            sourcefile.write(_indent(1) + f'configButton(Panel::{name}, "{name}");\n')

        if knobs:
            sourcefile.write('\n')
        for knob in knobs:
            name = knob['name']
            sourcefile.write(_indent(1) + f'configParam(Panel::Knob_{name}, -1.f, 1.f, 0.f, "");\n')

        if inputs:
            sourcefile.write('\n')
        for input in inputs:
            name = input['name']
            sourcefile.write(_indent(1) + f'configInput(Panel::{name}, "{name}");\n')

        if outputs:
            sourcefile.write('\n')
        for output in outputs:
            name = output['name']
            sourcefile.write(_indent(1) + f'configOutput(Panel::{name}, "{name}");\n')

        sourcefile.write('}\n')

        sourcefile.write('\n')

        sourcefile.write(f'SvgPanel* {panelName}Widget::setup({panelName}* module)\n')
        sourcefile.write('{\n')
        sourcefile.write(_indent(1) + 'setModule(module);\n')
        sourcefile.write(_indent(1) + f'std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/{panelName}.svg");\n')
        sourcefile.write(_indent(1) + 'SvgPanel* mainPanel = createPanel(panelPath);\n')
        sourcefile.write(_indent(1) + 'setPanel(mainPanel);\n')

        if buttons:
            sourcefile.write('\n')
        for button in buttons:
            name = button['name']
            x = button['cx']
            y = button['cy']
            sourcefile.write(
                _indent(1) + f'addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec({x}, {y}), module, {panelName}::Panel::{name}, {panelName}::Panel::Red_{name}));\n')

        if knobs:
            sourcefile.write('\n')
        for knob in knobs:
            name = knob['name']
            x = knob['cx']
            y = knob['cy']
            sourcefile.write(_indent(1) + f'addParam(createParamCentered<RoundSmallBlackKnob>(Vec({x}, {y}), module, {panelName}::Panel::Knob_{name}));\n')

        if inputs:
            sourcefile.write('\n')
        for input in inputs:
            name = input['name']
            x = input['cx']
            y = input['cy']
            sourcefile.write(_indent(1) + f'addInput(createInputCentered<PJ301MPort>(Vec({x}, {y}), module, {panelName}::Panel::{name}));\n')

        if outputs:
            sourcefile.write('\n')
        for output in outputs:
            name = output['name']
            x = output['cx']
            y = output['cy']
            sourcefile.write(_indent(1) + f'addOutput(createOutputCentered<PJ301MPort>(Vec({x}, {y}), module, {panelName}::Panel::{name}));\n')

        if lights:
            sourcefile.write('\n')
        for light in lights:
            name = light['name']
            x = light['cx']
            y = light['cy']
            sourcefile.write(_indent(1) + f'addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec({x}, {y}), module, {panelName}::Panel::Red_{name}));\n')

        for meter in meters:
            name = meter['name']
            count = int(meter['count'])
            x = meter['rx']
            y = meter['cy']
            for index in range(count):
                sourcefile.write(
                    _indent(1) + f'addChild(createLightCentered<SmallLight<RedGreenBlueLight>>(Vec({x + 4.0 + (6.0 * index)}, {y}), module, {panelName}::Panel::Red_Segment{index+1}_{name}));\n')

        if displays:
            sourcefile.write('\n')
        for display in displays:
            name = display['name']
            count = display['count']
            x = display['rx']
            y = display['ry']
            sourcefile.write(_indent(1) + f'addChild(new SchweineSystem::LCDDisplay::Widget(Vec({x}, {y}), module, {count}, {panelName}::Panel::Value_{name}, {panelName}::Panel::Red_{name}));\n')

        sourcefile.write('\n')
        sourcefile.write(_indent(1) + 'return mainPanel;\n')

        sourcefile.write('}\n')
        sourcefile.write('\n')


def writeSources(modulesPath, subFolder, panelName, components):

    _writePanelSource(modulesPath, subFolder, panelName, components)

    if subFolder:
        fileName = modulesPath + '/src/' + subFolder + '/' + panelName + '.cpp'
    else:
        fileName = modulesPath + '/src/' + panelName + '.cpp'
    if os.path.exists(fileName):
        return

    with open(fileName, 'w') as sourcefile:
        sourcefile.write(f'#include "{panelName}.h"\n')
        sourcefile.write(f'#include "{panelName}Panel.h"\n')
        sourcefile.write('\n')
        sourcefile.write('#include <SchweineSystemMaster.h>\n')
        sourcefile.write('\n')

        sourcefile.write(f'{panelName}::{panelName}()\n')
        sourcefile.write('   : Module()\n')
        sourcefile.write('{\n')
        sourcefile.write(_indent(1) + 'setup();\n')
        sourcefile.write('}\n')

        sourcefile.write('\n')

        sourcefile.write(f'{panelName}::~{panelName}()\n')
        sourcefile.write('{\n')
        sourcefile.write('}\n')

        sourcefile.write('\n')

        sourcefile.write(f'void {panelName}::process(const ProcessArgs& args)\n')
        sourcefile.write('{\n')
        sourcefile.write('}\n')
        sourcefile.write('\n')

        sourcefile.write(f'{panelName}Widget::{panelName}Widget({panelName}* module)\n')
        sourcefile.write(f': ModuleWidget()\n')
        sourcefile.write('{\n')
        sourcefile.write(_indent(1) + 'SvgPanel* mainPanel = setup(module);\n')
        sourcefile.write(_indent(1) + '(void)mainPanel;\n')
        sourcefile.write('}\n')
        sourcefile.write('\n')

        sourcefile.write(f'Model* model{panelName} = SchweineSystem::Master::the()->addModule<{panelName}, {panelName}Widget>("{panelName}");\n')
        sourcefile.write('\n')
