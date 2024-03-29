#!/usr/bin/env python3

import argparse
import os
import pathlib
import shutil
import json

from libmodule import createPanel, getPanelComponents
from libmodule import Header, Source, Panel

modulesPath = os.path.realpath(__file__)
modulesPath = os.path.dirname(modulesPath)


class Module:

    def __init__(self):

        self._modules = dict()
        self._gatheredList = list()

        def buildResourceDict(path):

            for entry in os.scandir(path):
                if entry.is_dir():
                    buildResourceDict(entry.path)
                elif not entry.is_file():
                    continue
                if not entry.name.endswith('.svg'):
                    continue

                name = entry.name.replace('.svg', '')
                master = os.path.dirname(entry.path) + '/' + name + '.afdesign'
                master = master.replace(modulesPath + '/res', modulesPath + '/panels')
                if not os.path.exists(master):
                    continue

                mtime = os.path.getmtime(entry.path)
                self._modules[name] = dict()
                self._modules[name]['rc_path'] = entry.path
                self._modules[name]['rc_mtime'] = mtime

        def addSourceInformation(path):

            for entry in os.scandir(path):
                if entry.is_dir():
                    if entry.name.startswith('_'):
                        continue
                    addSourceInformation(entry.path)
                elif not entry.is_file():
                    continue
                if not entry.name.endswith('.hpp'):
                    continue

                name = entry.name.replace('.hpp', '')
                if not name in self._modules:
                    continue
                mtime = os.path.getmtime(entry.path)
                self._modules[name]['source_path'] = os.path.dirname(entry.path)
                self._modules[name]['panel_mtime'] = mtime

        buildResourceDict(modulesPath + '/res/')
        addSourceInformation(modulesPath + '/src/')

        self._gather()

    def update(self, name):

        if name:
            self._updateModule(name)
            return

        for module in self._gatheredList:
            self._updateModule(module)

        for module, data in self._modules.items():
            if not 'panel_mtime' in data:
                sourcePath = os.path.dirname(data['rc_path'])
                sourcePath = sourcePath.replace('/res/', '/src/')
                os.makedirs(sourcePath, exist_ok=True)
                data['source_path'] = sourcePath

                self._updateModule(module)
            else:
                diffTime = data['rc_mtime'] - data['panel_mtime']
                if diffTime < 0:
                    continue

                self._updateModule(module)

    def _updateModule(self, moduleName):

        if not moduleName in self._modules:
            print(f'no panel found with name {moduleName}')
            return

        print(moduleName)
        panelFileName = self._modules[moduleName]['rc_path']
        [componentMap, metaMap] = getPanelComponents(panelFileName)
        for key, value in componentMap.items():
            print(f'* {key} x {len(value)}')
            # print(value)

        sourcePath = self._modules[moduleName]['source_path']
        panelFileName = panelFileName.replace(modulesPath + '/', '')

        headers = Header(sourcePath, moduleName, panelFileName, componentMap, metaMap)
        headers.write()

        sources = Source(sourcePath,  moduleName, panelFileName, componentMap, metaMap)
        sources.write()

        panel = Panel(sourcePath,  moduleName, panelFileName, componentMap, metaMap)
        panel.write()

        with open(modulesPath + '/plugin.json', 'r') as infile:
            content = json.load(infile)

        for module in content['modules']:
            slugName = module['slug']
            if slugName == moduleName:
                return

        slugDict = {
            'slug': moduleName,
            'name': moduleName,
            'description': str(),
            'tags': list()
        }

        content['modules'].append(slugDict)

        with open(modulesPath + '/plugin.json', 'w') as outfile:
            json.dump(content, outfile, indent=3)

    def _gather(self):

        desktop = str(pathlib.Path.home()) + '/Desktop'
        if not os.path.exists(desktop):
            return

        for entry in os.scandir(desktop):
            if not entry.is_file():
                continue
            if not entry.name.endswith('.svg'):
                continue

            if entry.name.endswith('.svg'):
                name = entry.name.replace('.svg', '')

            if not name in self._modules:
                continue

            targetPath = self._modules[name]['rc_path']
            targetPath = os.path.dirname(targetPath)
            print(f'.... gather {name} -> {targetPath}')

            self._gatheredList.append(name)
            shutil.move(entry.path, targetPath + '/' + entry.name)


def main():

    parser = argparse.ArgumentParser(description='do things with modules.')
    parser.add_argument('module', metavar='MODULE', type=str, nargs='?', help='a module name')
    parser.add_argument('-c', '--create', type=int, nargs=1, help='creates and empty SVG file with given HP')
    parser.add_argument('-u', '--update', action='store_true', help='update or create a module for an existing svg file')

    args = parser.parse_args()  # will quit here if help is called

    if not args.create and not args.update:
        parser.print_help()
        return

    if args.create:
        moduleName = args.module
        panelPath = modulesPath + '/res/'
        hpWidth = args.create[0]
        createPanel(panelPath, moduleName, hpWidth)
    elif args.update:
        module = Module()
        module.update(args.module)


if __name__ == '__main__':
    main()
