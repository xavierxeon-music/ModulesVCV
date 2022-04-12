#!/usr/bin/env python3

import os


def _indent(level):

    return ' ' * (3 * level)


def _addComponents(headerfile, components):

    params = components['params']
    inputs = components['inputs']
    outputs = components['outputs']
    lights = components['lights']
    widgets = components['widgets']

    headerfile.write(_indent(1) + 'enum ParamId\n')
    headerfile.write(_indent(1) + '{\n')
    for param in params:
        name = param['name']
        headerfile.write(_indent(2) + f'{name},\n')
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
        headerfile.write(_indent(2) + f'{name},\n')
    headerfile.write(_indent(2) + 'LIGHTS_LEN\n')
    headerfile.write(_indent(1) + '};\n')
    headerfile.write('\n')


def _writeDataHeader(modulesPath, panelName, components):

    fileName = modulesPath + '/src/' + panelName + 'Data.h'

    with open(fileName, 'w') as headerfile:
        headerfile.write(f'#ifndef {panelName}DataH\n')
        headerfile.write(f'#define {panelName}DataH\n')
        headerfile.write('\n')
        headerfile.write(f'#include "{panelName}.h"\n')
        headerfile.write('\n')

        headerfile.write(f'struct {panelName}::Data\n')
        headerfile.write('{\n')

        _addComponents(headerfile, components)

        headerfile.write('};\n')

        headerfile.write('\n')
        headerfile.write(f'#endif // {panelName}DataH\n')


def writeHeaders(modulesPath, panelName, components):

    _writeDataHeader(modulesPath, panelName, components)

    fileName = modulesPath + '/src/' + panelName + '.h'
    # if os.path.exists(fileName):
    #    return

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
        headerfile.write(_indent(1) + 'struct Data;\n')
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

        headerfile.write(f'struct {panelName}Widget : ModuleWidget\n')
        headerfile.write('{\n')
        headerfile.write(_indent(1) + f'{panelName}Widget({panelName}* module);\n')
        headerfile.write('};\n')
        headerfile.write('\n')
        headerfile.write(f'#endif // {panelName}H\n')


def _writeDataSource(modulesPath, panelName, components):

    fileName = modulesPath + '/src/' + panelName + 'Data.cpp'

    params = components['params']
    inputs = components['inputs']
    outputs = components['outputs']
    lights = components['lights']
    widgets = components['widgets']

    with open(fileName, 'w') as sourcefile:
        sourcefile.write(f'#include "{panelName}.h"\n')
        sourcefile.write(f'#include "{panelName}Data.h"\n')
        sourcefile.write('\n')
        sourcefile.write('#include "Schweinesystem.h"\n')
        sourcefile.write('\n')

        sourcefile.write(f'void {panelName}::setup()\n')
        sourcefile.write('{\n')
        sourcefile.write(_indent(1) + 'config(Data::PARAMS_LEN, Data::INPUTS_LEN, Data::OUTPUTS_LEN, Data::LIGHTS_LEN);\n')
        if params:
            sourcefile.write('\n')
        for param in params:
            name = param['name']
            sourcefile.write(_indent(1) + f'configParam(Data::{name}, 0.f, 1.f, 0.f, "");\n')
        if inputs:
            sourcefile.write('\n')
        for input in inputs:
            name = input['name']
            sourcefile.write(_indent(1) + f'configInput(Data::{name}, "");\n')
        if outputs:
            sourcefile.write('\n')
        for output in outputs:
            name = output['name']
            sourcefile.write(_indent(1) + f'configOutput(Data::{name}, "");\n')
        if lights:
            sourcefile.write('\n')
        for light in lights:
            name = light['name']
        sourcefile.write('}\n')

        sourcefile.write('\n')

        sourcefile.write(f'{panelName}Widget::{panelName}Widget({panelName}* module)\n')
        sourcefile.write('{\n')
        sourcefile.write(_indent(1) + 'setModule(module);\n')
        sourcefile.write(_indent(1) + f'std::string panelPath = asset::plugin(Schweinesystem::instance(), "res/{panelName}.svg");\n')
        sourcefile.write(_indent(1) + 'SvgPanel* mainPanel = createPanel(panelPath);\n')
        sourcefile.write(_indent(1) + 'setPanel(mainPanel);\n')
        if params:
            sourcefile.write('\n')
        for param in params:
            name = param['name']
            cx = param['cx']
            cy = param['cy']
            sourcefile.write(_indent(1) + f'addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec({cx}, {cy})), module, {panelName}::Data::{name}));\n')
        if inputs:
            sourcefile.write('\n')
        for input in inputs:
            name = input['name']
            cx = input['cx']
            cy = input['cy']
            sourcefile.write(_indent(1) + f'addInput(createInputCentered<PJ301MPort>(mm2px(Vec({cx}, {cy})), module, {panelName}::Data::{name}));\n')
        if outputs:
            sourcefile.write('\n')
        for output in outputs:
            name = output['name']
            cx = output['cx']
            cy = output['cy']
            sourcefile.write(_indent(1) + f'addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec({cx}, {cy})), module, {panelName}::Data::{name}));\n')
        if lights:
            sourcefile.write('\n')
        for light in lights:
            name = light['name']
            cx = light['cx']
            cy = light['cy']
            sourcefile.write(_indent(1) + f'addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec({cx}, {cy})), module, {panelName}::Data::{name}));\n')
        sourcefile.write('}\n')


def writeSources(modulesPath, panelName, components):

    _writeDataSource(modulesPath, panelName, components)

    fileName = modulesPath + '/src/' + panelName + '.cpp'
    # if os.path.exists(fileName):
    #    return

    with open(fileName, 'w') as sourcefile:
        sourcefile.write(f'#include "{panelName}.h"\n')
        sourcefile.write(f'#include "{panelName}Data.h"\n')
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

        sourcefile.write(f'void {panelName}::process(const ProcessArgs& args)\n')
        sourcefile.write('{\n')
        sourcefile.write('}\n')
