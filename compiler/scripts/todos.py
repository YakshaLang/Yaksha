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
import argparse
import json
import os
import re


def find_files(directory, extensions):
    files = []
    for root, _, filenames in os.walk(directory):
        for filename in filenames:
            if filename.endswith(extensions):
                files.append(os.path.join(root, filename))
    return files


def queue_pop_or_empty(queue):
    if queue:
        return queue[-1]
    else:
        return ""


def meta(queue, queue_classes, queue_namespaces, queue_func):
    current_index = 0
    if queue:
        current_index = queue[0]
        queue.pop(0)
    current_namespace = queue_pop_or_empty(queue_namespaces)
    current_class = queue_pop_or_empty(queue_classes)
    current_func = queue_pop_or_empty(queue_func)
    metadata = {
        "namespace": current_namespace,
        "class": current_class,
        "line": current_index,
        "function": current_func,
    }
    return metadata


def extract_comments(file_path):
    comments = []
    queue_line = []
    queue_namespaces = []
    queue_classes = []
    queue_func = []
    with open(file_path, 'r', encoding='utf-8', errors='ignore') as file:
        lines = file.readlines()
        multiline_comment = False
        combined_single_line_comment = ""
        for i, line in enumerate(lines):
            line = line.strip()

            # Check for namespace, class, function, and member function
            namespace_match = re.search(r'(?:using\s+)?namespace\s+([a-zA-Z0-9_]+)\s*{', line)
            class_match = re.search(r'(?:class|struct)\s+([a-zA-Z0-9_]+)\s*[{:]', line)
            member_function_match = re.search(r'([a-zA-Z0-9_]+)\s+([a-zA-Z0-9_]+)\s*\(', line)
            function_match = re.search(r'([a-zA-Z0-9_]+)\s*\(', line)

            # Variables to keep track of context within the file
            if namespace_match:
                current_namespace = ".".join(namespace_match.groups())
                queue_namespaces.append(current_namespace)
            if class_match:
                current_class = ".".join(class_match.groups())
                queue_classes.append(current_class)
            if member_function_match:
                queue_func.append(".".join(member_function_match.groups()))
            elif function_match:
                queue_func.append(".".join(function_match.groups()))
            # Check for multiline comments
            queue_line.append(i)
            if '/*' in line:
                multiline_comment = True
                combined_single_line_comment = line.split('/*')[0]
            elif '*/' in line:
                multiline_comment = False
                combined_single_line_comment += line.split('*/')[1]
                metadata = meta(queue_line, queue_classes, queue_namespaces, queue_func)
                comments.append((metadata, combined_single_line_comment))
            elif multiline_comment:
                combined_single_line_comment += "\n" + line
            elif '//' in line:
                # Single line comment
                combined_single_line_comment += ("\n" + line.split('//')[1])
            elif combined_single_line_comment:
                metadata = meta(queue_line, queue_classes, queue_namespaces, queue_func)
                comments.append((metadata, combined_single_line_comment))
                combined_single_line_comment = ""

    return comments


def find_todo_comments(comments, file_path):
    todo_comments = []
    for metadata, comment in comments:
        match = re.search(r'\b(TODO|FIXME)\b', comment)
        if match:
            todo_comments.append({
                "file": os.path.relpath(file_path),
                "line": metadata["line"],
                "comment": comment,
                "class": metadata["class"],
                "namespace": metadata["namespace"],
                "function": metadata["function"],
            })
    return todo_comments


def display_comments(file_path, comments, show_file):
    if show_file:
        print(f"\n\033[36mFile: {file_path}\033[0m")

    for comment in comments:
        print(f"\033[33m{comment['comment'].strip()}\033[0m")
        meta_dt = [f"line: \033[32m{comment['line']}\033[0m"]
        if comment['namespace']:
            meta_dt.append(f"namespace: \033[34m{comment['class']}\033[0m")
        if comment['class']:
            meta_dt.append(f"class: \033[34m{comment['class']}\033[0m")
        if comment['function']:
            meta_dt.append(f"fn: \033[34m{comment['function']}\033[0m")
        if meta_dt and show_file:
            print(', '.join(meta_dt))


def save_to_json(todo_comments, output_json):
    with open(output_json, 'w') as json_file:
        json.dump(todo_comments, json_file, indent=2)


def main():
    parser = argparse.ArgumentParser(description="Extract and display TODO comments from C/C++ source files.")
    parser.add_argument("directory", help="Directory to search for C/C++ files.")
    parser.add_argument("--show-file", action="store_true", help="Show file and line number for each TODO comment.")
    parser.add_argument("--output-json", help="Save TODO comments to a JSON file.")
    args = parser.parse_args()

    c_cpp_files = find_files(args.directory, ('.c', '.cpp', '.h', '.hpp'))

    all_todo_comments = []
    for file_path in c_cpp_files:
        comments = extract_comments(file_path)
        todo_comments = find_todo_comments(comments, file_path)
        all_todo_comments.extend(todo_comments)

        if todo_comments and not args.output_json:
            display_comments(file_path, todo_comments, args.show_file)

    if args.output_json:
        save_to_json(all_todo_comments, args.output_json)


if __name__ == "__main__":
    main()
