#!/usr/bin/env python3

import re
import xml.etree.ElementTree as et


def createPanel(panelFileName, hpWidth):

    root = et.Element('svg')
    root.set('width', '100%')
    root.set('height', '100%')
    root.set('viewBox', '0 0 ' + str(60 * 14.4) + ' 365')
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


def _removeXMLNamespace(root):

    def remove_namespace1(s):
        if s.startswith("{"):
            return s[s.find("}")+1:]
        else:
            return s

    for elem in root.iter():
        elem.tag = remove_namespace1(elem.tag)
        elem.attrib = dict([(remove_namespace1(k), v) for (k, v) in elem.attrib.items()])


def addInkscpaeAtributes(panelFileName):

    tree = et.parse(panelFileName)
    root = tree.getroot()

    if root.get('processed'):
        return

    _removeXMLNamespace(root)

    styleMap = {
        'fill:rgb(0,255,0);': 'fill:#00ff00;',
        'fill:rgb(0,0,255);': 'fill:#0000ff;',
        'fill:rgb(255,0,255);': 'fill:#ff00ff;',
        'fill:rgb(255,0,0);': 'fill:#ff0000;',
    }

    # see https://developer.mozilla.org/en-US/docs/Web/SVG/Attribute/transform
    def _transform(group, x, y):

        transform = group.get('transform')
        transform = transform.replace('matrix(', '')
        transform = transform.replace(')', '')
        coeff = transform.split(',')
        coeff = [float(x) for x in coeff]

        x = coeff[0] * x + coeff[2] * cy + coeff[4]
        y = coeff[1] * x + coeff[3] * y + coeff[5]

        return [x, y]

    # find and alter compnents
    for group in root:
        if 'g' != group.tag:
            continue

        groupId = group.get('id')
        if None == groupId or 'components' != groupId:
            continue

        # group.set('inkscape:groupmode', 'layer')
        group.set('groupmode', 'layer')
        # group.set('inkscape:label', 'components')
        group.set('label', 'components')

        removeGroupList = list()
        for subGroup in group:
            if 'g' != subGroup.tag:
                continue

            subGroupId = subGroup.get('id')

            shape = subGroup.find('circle')
            cx = float(shape.get('cx'))
            cy = float(shape.get('cy'))

            cx, cy = _transform(subGroup, cx, cy)
            cx, cy = _transform(group, cx, cy)

            shape.set('cx', str(cx))
            shape.set('cy', str(cy))

            shape.set('inkscape:label', subGroupId)
            # circle.set('label', subGroupId)

            style = shape.get('style')
            if style in styleMap:
                shape.set('style', styleMap[style])

            group.append(shape)

            removeGroupList.append(subGroup)

        for subGroup in removeGroupList:
            group.remove(subGroup)

        if 'transform' in group.attrib:
            del group.attrib['transform']

    # write back file
    root.set('xmlns', 'http://www.w3.org/2000/svg')
    root.set('xmlns:svg', 'http://www.w3.org/1999/xlink')
    root.set('xmlns:inkscape', 'http://www.inkscape.org/namespaces/inkscape')
    root.set('processed', 'true')
    tree.write(panelFileName, encoding='UTF-8', xml_declaration=True, short_empty_elements=False)


def _str_to_identifier(s):
    if not s:
        return "_"
    # Identifiers can't start with a number
    if s[0].isdigit():
        s = "_" + s
    # Capitalize first letter
    s = s[0].upper() + s[1:]
    # Replace special characters with underscore
    s = re.sub(r'\W', '_', s)
    return s


def getPanelComponents(panelFileName):

    tree = et.parse(panelFileName)

    ns = {
        "svg": "http://www.w3.org/2000/svg",
        "inkscape": "http://www.inkscape.org/namespaces/inkscape",
    }

    root = tree.getroot()
    # Get SVG scale relative to mm
    root_height = root.get('height')
    if root_height.endswith("mm"):
        scale = 1
    else:
        svg_dpi = 75
        mm_per_in = 25.4
        scale = mm_per_in / svg_dpi

    # Get components layer
    group = root.find(".//svg:g[@inkscape:label='components']", ns)
    # Illustrator uses `data-name` (in Unique object ID mode) or `id` (in Layer Names object ID mode) for the group name.
    # Don't test with `not group` since Elements with no subelements are falsy.
    if group is None:
        group = root.find(".//svg:g[@data-name='components']", ns)
    if group is None:
        group = root.find(".//svg:g[@id='components']", ns)
    if group is None:
        return

    components = {}
    components['params'] = []
    components['inputs'] = []
    components['outputs'] = []
    components['lights'] = []
    components['widgets'] = []

    for el in group:
        c = {}

        # Get name
        name = el.get('{' + ns['inkscape'] + '}label')
        # Illustrator names
        if not name:
            name = el.get('data-name')
        if not name:
            name = el.get('id')
        if not name:
            name = ""
        # Split name and component class name
        names = name.split('#', 1)
        name = names[0]

        if len(names) >= 2:
            c['cls'] = names[1]
        name = _str_to_identifier(name).upper()
        c['name'] = name

        # Get position
        if el.tag == '{' + ns['svg'] + '}rect':
            x = float(el.get('x')) * scale
            y = float(el.get('y')) * scale
            width = float(el.get('width')) * scale
            height = float(el.get('height')) * scale
            c['x'] = round(x, 3)
            c['y'] = round(y, 3)
            c['width'] = round(width, 3)
            c['height'] = round(height, 3)
            c['cx'] = round(x + width / 2, 3)
            c['cy'] = round(y + height / 2, 3)
        elif el.tag == '{' + ns['svg'] + '}circle' or el.tag == '{' + ns['svg'] + '}ellipse':
            cx = float(el.get('cx')) * scale
            cy = float(el.get('cy')) * scale
            c['cx'] = round(cx, 3)
            c['cy'] = round(cy, 3)
        else:
            print(f"Element in components layer is not rect, circle, or ellipse: {el}")
            continue

        # Get color
        color = None
        # Get color from fill attribute
        fill = el.get('fill')
        if fill:
            color = fill
        # Get color from CSS fill style
        if not color:
            style = el.get('style')
            if style:
                color_match = re.search(r'fill:\S*(#[0-9a-fA-F]{6})', style)
                color = color_match.group(1)
        if not color:
            print(f"Cannot get color of component: {el}")
            continue

        color = color.lower()

        if color == '#ff0000' or color == '#f00' or color == 'red':
            components['params'].append(c)
        if color == '#00ff00' or color == '#0f0' or color == 'lime':
            components['inputs'].append(c)
        if color == '#0000ff' or color == '#00f' or color == 'blue':
            components['outputs'].append(c)
        if color == '#ff00ff' or color == '#f0f' or color == 'magenta':
            components['lights'].append(c)
        if color == '#ffff00' or color == '#ff0' or color == 'yellow':
            components['widgets'].append(c)

    # Sort components
    def top_left_sort(w): return w['cy'] + 0.01 * w['cx']
    components['params'] = sorted(components['params'], key=top_left_sort)
    components['inputs'] = sorted(components['inputs'], key=top_left_sort)
    components['outputs'] = sorted(components['outputs'], key=top_left_sort)
    components['lights'] = sorted(components['lights'], key=top_left_sort)
    components['widgets'] = sorted(components['widgets'], key=top_left_sort)

    print(f"Found {len(components['params'])} params, {len(components['inputs'])} inputs, {len(components['outputs'])} outputs, {len(components['lights'])} lights, and {len(components['widgets'])} custom widgets in \"components\" layer.")
    return components
