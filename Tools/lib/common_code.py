#!/usr/bin/env python3

import os


class Common:

    def __init__(self, sourcePath,  moduleName, panelFileName, components):

        self.moduleName = moduleName
        self.panelFileName = panelFileName
        self._fileNameBase = sourcePath + '/' + moduleName

        self.buttons = components['button'] if components and 'button' in components else list()
        self.inputs = components['input'] if components and 'input' in components else list()
        self.knobs = components['knob'] if components and 'knob' in components else list()
        self.lcds = components['lcd'] if components and 'lcd' in components else list()
        self.ledbuttons = components['ledbutton'] if components and 'ledbutton' in components else list()
        self.leds = components['led'] if components and 'led' in components else list()
        self.meters = components['meter'] if components and 'meter' in components else list()
        self.oleds = components['oled'] if components and 'oled' in components else list()
        self.outputs = components['output'] if components and 'output' in components else list()
        self.switches = components['switch'] if components and 'switch' in components else list()

    def compileFileName(self, rest):

        return self._fileNameBase + rest

    def _lineFunction(self, fileHandler):

        def __line(indentLevl: int, text=str()):
            indent = ' ' * (3 * indentLevl)
            fileHandler.write(indent + text + '\n')

        return __line
