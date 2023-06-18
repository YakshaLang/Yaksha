import subprocess
import tkinter as tk
import tkinter.messagebox
from tkinter.scrolledtext import ScrolledText
import os

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
