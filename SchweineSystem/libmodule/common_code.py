#!/usr/bin/env python3

import os


class Common:

    def __init__(self, sourcePath,  moduleName, panelFileName, componentMap, metaMap):

        self.moduleName = moduleName
        self.panelFileName = panelFileName
        self._fileNameBase = sourcePath + '/' + moduleName

        self.namespace = metaMap['namespace'] if metaMap and 'namespace' in metaMap else None

        self.buttons = componentMap['button'] if componentMap and 'button' in componentMap else list()
        self.inputs = componentMap['input'] if componentMap and 'input' in componentMap else list()
        self.knobs = componentMap['knob'] if componentMap and 'knob' in componentMap else list()
        self.lcds = componentMap['lcd'] if componentMap and 'lcd' in componentMap else list()
        self.ledbuttons = componentMap['ledbutton'] if componentMap and 'ledbutton' in componentMap else list()
        self.leds = componentMap['led'] if componentMap and 'led' in componentMap else list()
        self.meters = componentMap['meter'] if componentMap and 'meter' in componentMap else list()
        self.oleds = componentMap['oled'] if componentMap and 'oled' in componentMap else list()
        self.outputs = componentMap['output'] if componentMap and 'output' in componentMap else list()
        self.sliders = componentMap['slider'] if componentMap and 'slider' in componentMap else list()
        self.switches = componentMap['switch'] if componentMap and 'switch' in componentMap else list()

    def compileFileName(self, rest):

        return self._fileNameBase + rest

    def _lineFunction(self, fileHandler):

        def __line(indentLevl: int, text=str()):
            indent = ' ' * (3 * indentLevl)
            fileHandler.write(indent + text + '\n')

        return __line
