# ==============================================================================================
# ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
# ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
# ╩═╝┴└─┘└─┘┘└┘└─┘└─┘
# Note: libs - MIT license, runtime/3rd - various
# ==============================================================================================
# GPLv3:
#
# Yaksha - Programming Language.
# Copyright (C) 2020 - 2024 Bhathiya Perera
#
# This program is free software: you can redistribute it and/or modify it under the terms
# of the GNU General Public License as published by the Free Software Foundation,
# either version 3 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with this program.
# If not, see https://www.gnu.org/licenses/.
#
# ==============================================================================================
# Additional Terms:
#
# Please note that any commercial use of the programming language's compiler source code
# (everything except compiler/runtime, compiler/libs and compiler/3rd) require a written agreement
# with author of the language (Bhathiya Perera).
#
# If you are using it for an open source project, please give credits.
# Your own project must use GPLv3 license with these additional terms.
#
# You may use programs written in Yaksha/YakshaLisp for any legal purpose
# (commercial, open-source, closed-source, etc) as long as it agrees
# to the licenses of linked runtime libraries (see compiler/runtime/README.md).
#
# ==============================================================================================
import json
import os
import xml.etree.ElementTree as ElementTree

RUNTIME_PATH = os.path.join(os.path.dirname(__file__), "..", "runtime")
RUNTIME_DOCS_DOCKERFILE = os.path.join(os.path.dirname(__file__), "..", "runtime_docs.Dockerfile")
OUTPUT_PATH = os.path.join(os.path.dirname(__file__), "..", "comp_output_test")

def cleanup_json_data(json_data):
    children = json_data.get('children', [])
    temp_dictionary = {}
    temp_set = set()
    result = []
    for child in children:
        if 'name' not in child:
            result.append(child)
            continue
        if child['type'] == 'typedef':
            child['datatype'] = child['datatype'][0]
        if child['type'] == 'variable' and child['datatype'] == 'struct':
            continue
        if child['type'] == 'typedef' and 'datatype' in child and child['datatype'] == 's':
            continue
        if child['name'] in temp_dictionary:
            already_discovered = temp_dictionary[child['name']]
            serialized_child = json.dumps(child, sort_keys=True)
            already_discovered_serialized = json.dumps(already_discovered, sort_keys=True)
            if serialized_child == already_discovered_serialized:
                continue
            if serialized_child in temp_set:
                continue
            temp_set.add(serialized_child)
        temp_dictionary[child['name']] = child
        result.append(child)
    json_data['children'] = result
    return json_data

def xml_to_json(xml_string):
    root = ElementTree.fromstring(xml_string)
    namespace = '{https://www.msweet.org}'

    def parse_element(element):
        result = {}
        for child in element:
            if child.tag in [f'{namespace}struct', f'{namespace}typedef', f'{namespace}variable',
                             f'{namespace}function', f'{namespace}enumeration',
                             f"{namespace}constant",
                             f"{namespace}union", f"{namespace}argument",
                             f"{namespace}returnvalue"
                             ]:
                if 'children' not in result:
                    result['children'] = []
                child_result = {'type': child.tag.replace(namespace, "")}
                if 'name' in child.attrib:
                    child_result['name'] = child.attrib['name']
                content = child.text.strip() if child.text else ''
                if content:
                    child_result['content'] = content
                child_result.update(parse_element(child))
                result['children'].append(child_result)
            elif child.tag in [f"{namespace}type", f"{namespace}description"]:
                key = child.tag.replace(namespace, "")
                if key == "type":
                    key = "datatype"
                if 'name' in child.attrib:
                    result['name'] = child.attrib['name']
                content = child.text.strip() if child.text else ''
                if key in result:
                    if isinstance(result[key], list):
                        result[key].append(content)
                    else:
                        result[key] = [result[key], content]
                else:
                    result[key] = content
            else:
                print(f"Unknown tag: {child.tag}")
        return result

    json_data = cleanup_json_data(parse_element(root))
    return json.dumps(json_data, indent=2)


def main():
    os.chdir(os.path.dirname(os.path.dirname(__file__)))
    os.system(f"docker build -t yaksha-runtime-docs -f {RUNTIME_DOCS_DOCKERFILE} .")
    os.system(f"docker run -v {RUNTIME_PATH}:/runtime -v {OUTPUT_PATH}:/output yaksha-runtime-docs")
    with open(os.path.join(OUTPUT_PATH, "runtime.xml")) as f:
        xml_string = f.read()
    json_string = xml_to_json(xml_string)
    with open(os.path.join(OUTPUT_PATH, "runtime.json"), "w") as f:
        f.write(json_string)


if __name__ == "__main__":
    main()
