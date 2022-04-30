#!/usr/bin/env python3

import os


class Common:

    def __init__(self, modulesPath, subFolder, moduleName, components):

        self.moduleName = moduleName

        if subFolder:
            self._fileNameBase = modulesPath + '/src/' + subFolder + '/' + moduleName
        else:
            self._fileNameBase = modulesPath + '/src/' + moduleName

        self.buttons = components['button'] if components and 'button' in components else list()
        self.displays = components['display'] if components and 'display' in components else list()
        self.inputs = components['input'] if components and 'input' in components else list()
        self.knobs = components['knob'] if components and 'knob' in components else list()
        self.ledbuttons = components['ledbutton'] if components and 'ledbutton' in components else list()
        self.lights = components['light'] if components and 'light' in components else list()
        self.meters = components['meter'] if components and 'meter' in components else list()
        self.oleds = components['oled'] if components and 'oled' in components else list()
        self.outputs = components['output'] if components and 'output' in components else list()

    def compileFileName(self, rest):

        return self._fileNameBase + rest

    def _lineFunction(self, fileHandler):

        def __line(indentLevl: int, text=str()):
            indent = ' ' * (3 * indentLevl)
            fileHandler.write(indent + text + '\n')

        return __line
