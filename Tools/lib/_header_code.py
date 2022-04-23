#!/usr/bin/env python3

import os


def _indent(self, level):

    return ' ' * (3 * level)


def _addComponents(headerfile, components):

    buttons = components['button'] if components and 'button' in components else list()
    displays = components['display'] if components and 'display' in components else list()
    inputs = components['input'] if components and 'input' in components else list()
    knobs = components['knob'] if components and 'knob' in components else list()
    lights = components['light'] if components and 'light' in components else list()
    meters = components['meter'] if components and 'meter' in components else list()
    outputs = components['output'] if components and 'output' in components else list()

    headerfile.write(_indent(1) + 'enum ParamId\n')
    headerfile.write(_indent(1) + '{\n')
    for button in buttons:
        name = button['name']
        headerfile.write(_indent(2) + f'{name},\n')
    for display in displays:
        name = display['name']
        headerfile.write(_indent(2) + f'Value_{name},\n')
    for knob in knobs:
        name = knob['name']
        headerfile.write(_indent(2) + f'Knob_{name},\n')
    headerfile.write(_indent(2) + 'PARAMS_LEN\n')
    headerfile.write(_indent(1) + '};\n')
    headerfile.write('\n')

    headerfile.write(_indent(1) + 'enum InputId\n')
    headerfile.write(_indent(1) + '{\n')
    for input in inputs:
        name = input['name']
        headerfile.write(_indent(2) + f'{name},\n')
    headerfile.write(_indent(2) + 'INPUTS_LEN\n')
    headerfile.write(_indent(1) + '};\n')
    headerfile.write('\n')

    headerfile.write(_indent(1) + 'enum OutputId\n')
    headerfile.write(_indent(1) + '{\n')
    for output in outputs:
        name = output['name']
        headerfile.write(_indent(2) + f'{name},\n')
    headerfile.write(_indent(2) + 'OUTPUTS_LEN\n')
    headerfile.write(_indent(1) + '};\n')
    headerfile.write('\n')

    headerfile.write(_indent(1) + 'enum LightId\n')
    headerfile.write(_indent(1) + '{\n')
    for light in lights:
        name = light['name']
        headerfile.write(_indent(2) + f'Red_{name},\n')
        headerfile.write(_indent(2) + f'Green_{name},\n')
        headerfile.write(_indent(2) + f'Blue_{name},\n')
    for meter in meters:
        name = meter['name']
        count = int(meter['count'])
        for index in range(count):
            headerfile.write(_indent(2) + f'Red_Segment{index+1}_{name},\n')
            headerfile.write(_indent(2) + f'Green_Segment{index+1}_{name},\n')
            headerfile.write(_indent(2) + f'Blue_Segment{index+1}_{name},\n')
    for button in buttons:
        name = button['name']
        headerfile.write(_indent(2) + f'Red_{name},\n')
        headerfile.write(_indent(2) + f'Green_{name},\n')
        headerfile.write(_indent(2) + f'Blue_{name},\n')
    for display in displays:
        name = display['name']
        headerfile.write(_indent(2) + f'Red_{name},\n')
        headerfile.write(_indent(2) + f'Green_{name},\n')
        headerfile.write(_indent(2) + f'Blue_{name},\n')
    headerfile.write(_indent(2) + 'LIGHTS_LEN\n')
    headerfile.write(_indent(1) + '};\n')
    headerfile.write('\n')


def _writePanelHeader(modulesPath, subFolder, panelName, components):

    if subFolder:
        fileName = modulesPath + '/src/' + subFolder + '/' + panelName + 'Panel.h'
    else:
        fileName = modulesPath + '/src/' + panelName + 'Panel.h'

    with open(fileName, 'w') as headerfile:
        headerfile.write(f'#ifndef {panelName}PanelH\n')
        headerfile.write(f'#define {panelName}PanelH\n')
        headerfile.write('\n')
        headerfile.write(f'#include "{panelName}.h"\n')
        headerfile.write('\n')

        headerfile.write(f'struct {panelName}::Panel\n')
        headerfile.write('{\n')

        _addComponents(headerfile, components)

        headerfile.write('};\n')

        headerfile.write('\n')
        headerfile.write(f'#endif // NOT {panelName}PanelH\n')


def writeHeaders(modulesPath, subFolder, panelName, components):

    _writePanelHeader(modulesPath, subFolder, panelName, components)

    if subFolder:
        fileName = modulesPath + '/src/' + subFolder + '/' + panelName + '.h'
    else:
        fileName = modulesPath + '/src/' + panelName + '.h'
    if os.path.exists(fileName):
        return

    with open(fileName, 'w') as headerfile:
        headerfile.write(f'#ifndef {panelName}H\n')
        headerfile.write(f'#define {panelName}H\n')
        headerfile.write('\n')
        headerfile.write('#include <rack.hpp>\n')
        headerfile.write('using namespace rack;\n')
        headerfile.write('\n')
        headerfile.write(f'class {panelName} : public Module\n')
        headerfile.write('{\n')

        headerfile.write('public:\n')
        headerfile.write(_indent(1) + 'struct Panel;\n')
        headerfile.write('\n')

        headerfile.write('public:\n')
        headerfile.write(_indent(1) + f'{panelName}();\n')
        headerfile.write(_indent(1) + f'~{panelName}();\n')
        headerfile.write('\n')
        headerfile.write('public:\n')
        headerfile.write(_indent(1) + 'void process(const ProcessArgs& args) override;\n')
        headerfile.write('\n')
        headerfile.write('private:\n')
        headerfile.write(_indent(1) + 'void setup();\n')
        headerfile.write('};\n')

        headerfile.write('\n')

        headerfile.write(f'class {panelName}Widget : public ModuleWidget\n')
        headerfile.write('{\n')
        headerfile.write('public:\n')
        headerfile.write(_indent(1) + f'{panelName}Widget({panelName}* module);\n')
        headerfile.write('\n')
        headerfile.write('private:\n')
        headerfile.write(_indent(1) + f'SvgPanel* setup({panelName}* module);\n')
        headerfile.write('};\n')
        headerfile.write('\n')
        headerfile.write(f'#endif // NOT {panelName}H\n')
