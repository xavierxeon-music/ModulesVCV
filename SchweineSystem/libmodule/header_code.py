#!/usr/bin/env python3

import os

from .common_code import Common


class Header(Common):

    def __init__(self,  sourcePath, moduleName, panelFileName, components, metaMap):

        Common.__init__(self,  sourcePath, moduleName, panelFileName, components, metaMap)

    def write(self):

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
            line(0, '#include <SvinModule.h>')
            line(0, '#include <SvinModuleWidget.h>')
            line(0)

            if self.buttons:
                line(0, '#include <SvinButton.h>')
            if self.knobs:
                line(0, '#include <SvinKnob.h>')
            if self.lcds:
                line(0, '#include <SvinDisplayLCD.h>')
            if self.ledbuttons:
                line(0, '#include <SvinButtonLED.h>')
            if self.leds:
                line(0, '#include <SvinLED.h>')
            if self.meters:
                line(0, '#include <SvinLightMeter.h>')
            if self.oleds:
                line(0, '#include <SvinDisplayOLED.h>')
            if self.sliders:
                line(0, '#include <SvinSlider.h>')
            if self.switches:
                line(0, '#include <SvinSwitch.h>')
            if self.inputs:
                line(0, '#include <SvinInput.h>')
            if self.outputs:
                line(0, '#include <SvinOutput.h>')
            line(0)

            baseIndent = 0
            className = self.moduleName
            if self.namespace:
                line(0, f'namespace {self.namespace}')
                line(0, '{')
                baseIndent = 1
                className = className.replace(self.namespace, '')

            line(baseIndent, f'class {className} : public Svin::Module')
            line(baseIndent, '{')
            line(baseIndent, 'public:')
            line(baseIndent + 1, 'struct Panel;')
            line(0)
            line(baseIndent, 'public:')
            line(baseIndent + 1, f'{className}();')
            line(baseIndent)
            line(baseIndent, 'public:')
            line(baseIndent + 1, 'void process(const ProcessArgs& args) override;')
            line(0)
            line(baseIndent, 'private:')
            line(baseIndent + 1, 'inline void setup();')
            line(baseIndent, '};')

            line(0)
            line(baseIndent, '// widget')
            line(0)

            line(baseIndent, f'class {className}Widget : public Svin::ModuleWidget')
            line(baseIndent, '{')
            line(baseIndent, 'public:')
            line(baseIndent + 1, f'{className}Widget({className}* module);')
            line(0)
            line(baseIndent, 'private:')
            line(baseIndent + 1, 'inline void setup();')
            line(baseIndent, '};')

            if self.namespace:
                line(0, '}')

            line(0)
            line(0, f'#ifndef {self.moduleName}HPP')
            line(0, f'#include "{self.moduleName}.hpp"')
            line(0, f'#endif // NOT {self.moduleName}HPP')

            line(0)

            line(0, f'#endif // NOT {self.moduleName}H')
