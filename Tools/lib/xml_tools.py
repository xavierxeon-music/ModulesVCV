#!/usr/bin/env python3

import re
import xml.etree.ElementTree as et


def createPanel(panelFileName, hpWidth):

    height = 380
    width = 15 * hpWidth

    root = et.Element('svg')
    root.set('width', '100%')
    root.set('height', '100%')
    root.set('viewBox', f'0 0 {width} {height}')
    root.set('version', '1.1')
    root.set('xmlns', 'http://www.w3.org/2000/svg')
    root.set('xmlns:xlink', 'http://www.w3.org/1999/xlink')
    root.set('xml:space', 'preserve')
    root.set('xmlns:serif', 'http://www.serif.com/')
    root.set('style', 'fill-rule:evenodd;clip-rule:evenodd;stroke-linejoin:round;stroke-miterlimit:2;')

    tree = et.ElementTree(root)
    # docType = '<!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">'
    et.indent(tree, space=" ", level=0)

    tree.write(panelFileName, encoding='UTF-8', xml_declaration=True, short_empty_elements=False)


def getPanelComponents(panelFileName):

    tree = et.parse(panelFileName)
    root = tree.getroot()

    # _removeXMLNamespace(root)
    componentMap = _compileComponentMap(root)

    for componentList in componentMap.values():
        for component in componentList:
            _compileFullName(component)
            hierachyList = component['hierachy']
            [x, y] = _compileCoordinates(hierachyList)
            if None == x or None == y:
                component['x'] = None
                component['y'] = None
            else:
                for group in hierachyList:
                    [x, y] = _transform(group, x, y)
                component['x'] = x
                component['y'] = y

            del component['hierachy']

    print(componentMap)
    return componentMap


def _compileFullName(component):

    name = component['name']

    hierachyList = component['hierachy']
    for group in hierachyList[1:]:
        groupId = group.get('id')
        if None == groupId:
            groupId = group.get('{http://www.serif.com/}id')
        if None == groupId:
            continue
        name = groupId + '_' + name

    component['name'] = name


def _transform(group, x, y):

    # see https://developer.mozilla.org/en-US/docs/Web/SVG/Attribute/transform

    transform = group.get('transform')
    if not transform:
        return [x, y]

    transform = transform.replace('matrix(', '')
    transform = transform.replace(')', '')
    coeff = transform.split(',')

    coeff = [float(x) for x in coeff]

    x = (coeff[0] * x) + (coeff[2] * y) + coeff[4]
    y = (coeff[1] * x) + (coeff[3] * y) + coeff[5]

    return [x, y]


def _compileComponentMap(root):

    parentMap = dict()

    def buildParentMap(parent):
        for child in parent:
            parentMap[child] = parent
            buildParentMap(child)
    buildParentMap(root)

    componentMap = dict()

    def groupCrawl(parent):

        for group in parent:
            groupCrawl(group)

            groupId = group.get('{http://www.serif.com/}id')
            if None == groupId:
                continue

            if not '#' in groupId:
                continue

            index = groupId.index('#')
            name = groupId[:index]
            typ = groupId[index + 1:]

            if not typ in componentMap:
                componentMap[typ] = list()

            hierachyList = list()
            parentGroup = group
            while parentGroup in parentMap:
                hierachyList.append(parentGroup)
                parentGroup = parentMap[parentGroup]

            groupDict = {'name': name, 'hierachy': hierachyList}
            componentMap[typ].append(groupDict)

    groupCrawl(root)

    return componentMap


def _compileCoordinates(hierachtList):

    if not hierachtList:
        return [None, None]

    def getCoordinate(element):

        if '{http://www.w3.org/2000/svg}circle' == element.tag:
            cx = float(element.get('cx'))
            cy = float(element.get('cy'))
            return [cx, cy]
        elif '{http://www.w3.org/2000/svg}rect' == element.tag:
            rx = float(element.get('x'))
            ry = float(element.get('y'))
            width = float(element.get('width'))
            height = float(element.get('height'))

            rx = rx + (0.5 * width)
            ry = ry + (0.5 * height)
            return [rx, ry]

        return [None, None]

    element = hierachtList[0]

    [x, y] = getCoordinate(element)
    if None != x and None != y:
        return [x, y]

    for child in element:
        [x, y] = getCoordinate(child)
        if None != x and None != y:
            return [x, y]

    return [None, None]
