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
import os
import subprocess
import tkinter as tk
import tkinter.messagebox
from tkinter.scrolledtext import ScrolledText

MAX_EXECUTION_TIME_SEC = 30
ROOT = os.path.dirname(os.path.abspath(__file__))


def execute(arg: str) -> (str, str, int):
    proc = subprocess.Popen(
        arg,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        encoding="utf-8",
        universal_newlines=True,
        shell=True)
    try:
        so, se = proc.communicate(timeout=MAX_EXECUTION_TIME_SEC)
        return_value = proc.returncode
    except subprocess.TimeoutExpired:
        proc.kill()
        proc.communicate()
        return "", "", -1
    return so.strip(), se.strip(), return_value


def get_text(w):
    return w.get("1.0", tkinter.END)


def set_text(w, txt):
    w.delete('1.0', tkinter.END)
    w.insert(tk.INSERT, txt)


class OutputTester:

    def __init__(self):
        self.out = None
        self.inp = None
        self.run_pp = None
        self.root = None

    def _run_pp(self):
        self._check_output("temp_file_please_delete.c", "zig cc -E %TEMP%")

    def _check_output(self, temp_file_name, command):
        text = get_text(self.inp)
        i_file = os.path.join(ROOT, temp_file_name)
        command_f = command.replace("%TEMP%", i_file)
        with open(i_file, "w+", encoding="utf-8") as h:
            h.write(text)
        so, se, r = execute(command_f)
        set_text(self.out, so + se)
        os.unlink(i_file)

    def start(self):
        self.root = tk.Tk()
        self.root.title("Output tester")
        self.root.resizable(False, False)
        self.run_pp = tk.Button(self.root, text="Run real C preprocessor", command=self._run_pp)
        self.inp = ScrolledText(self.root)
        self.out = ScrolledText(self.root)
        self.run_pp.pack()
        self.inp.pack()
        self.out.pack()
        self.root.mainloop()


if __name__ == "__main__":
    OutputTester().start()
