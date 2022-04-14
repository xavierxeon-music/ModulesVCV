#!/usr/bin/env python3

import argparse
import os
import pathlib
import shutil

from lib import createPanel, getPanelComponents
from lib import writeHeaders, writeSources

scriptPath = os.path.realpath(__file__)
scriptPath = os.path.dirname(scriptPath)

# TODO multiple module paths
modulesPath = os.path.abspath(scriptPath + '/../SchweineSystem')


def updateModule(panelName):

    panelFileName = modulesPath + '/res/' + panelName + '.svg'
    if not os.path.exists(panelFileName):
        print(f'no panel found with name {panelName}')

    components = getPanelComponents(panelFileName)
    print(components)

    writeHeaders(modulesPath, panelName, components)
    writeSources(modulesPath, panelName, components)


def gather():

    desktop = str(pathlib.Path.home()) + '/Desktop'

    for entry in os.scandir(desktop):
        if not entry.is_file():
            continue
        if not entry.name.endswith('.svg') and not entry.name.endswith('.afdesign'):
            continue
        print(entry.name)
        #shutil.copy(entry.path, modulesPath + '/res/' + entry.name)
        shutil.move(entry.path, modulesPath + '/res/' + entry.name)


def main():

    parser = argparse.ArgumentParser(description='do things with modules.')
    parser.add_argument('modulename', metavar='MODULE', type=str, nargs='?', help='the module name')
    parser.add_argument('-g', '--gather', action='store_true', help='move all svg and afdesign files from desktop to the res folder')
    parser.add_argument('-p', '--panel', type=int, nargs=1, help='creates and empty SVG file with given HP')
    parser.add_argument('-u', '--update', action='store_true', help='update or create a module for an existing svg file')

    args = parser.parse_args()  # will quit here if help is called

    # maybe gather
    if args.gather:
        gather()

    if args.panel and args.modulename:
        hpWidth = args.panel[0]
        panelFileName = modulesPath + '/res/' + args.modulename + '.svg'
        createPanel(panelFileName, hpWidth)
    elif args.update and args.modulename:
        updateModule(args.modulename)


if __name__ == '__main__':
    main()
