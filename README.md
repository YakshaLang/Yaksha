# Yaksha Programming Language

---------

![https://yakshalang.github.io/](https://yakshalang.github.io/imgs/yk-banner1.png)

[![.github/workflows/development.yml](https://github.com/YakshaLang/Yaksha/actions/workflows/development.yml/badge.svg)](https://github.com/YakshaLang/Yaksha/actions/workflows/development.yml)
[![.github/workflows/development_macos.yml](https://github.com/YakshaLang/Yaksha/actions/workflows/development_macos.yml/badge.svg)](https://github.com/YakshaLang/Yaksha/actions/workflows/development_macos.yml)
[![.github/workflows/release.yml](https://github.com/YakshaLang/Yaksha/actions/workflows/release.yml/badge.svg)](https://github.com/YakshaLang/Yaksha/actions/workflows/release.yml)
[![.github/workflows/release_macos.yml](https://github.com/YakshaLang/Yaksha/actions/workflows/release_macos.yml/badge.svg)](https://github.com/YakshaLang/Yaksha/actions/workflows/release_macos.yml)

# Documentation

* [📚 Standard Library](https://yakshalang.github.io/lib/)
* [🐣 Tutorials](https://yakshalang.github.io/tutorials/)
* [📄 Documentation](https://yakshalang.github.io/docs/)
* [💍 Proposals Repo](https://github.com/YakshaLang/yakshalang.github.io/tree/main/src/pages/yama) [📖 Read Proposals](https://yakshalang.github.io/yama/)
* [😈 Demos with source code](https://yakshalang.github.io/demos/)
* [⚽️ Playground](https://yaksha.pages.dev)
* [🤔 (B)log](https://yakshalang.github.io/blog/)
* [✅ Plan / Tasks](https://github.com/orgs/YakshaLang/projects/4/views/1)

# Communities

[![reddit](https://user-images.githubusercontent.com/498642/229309556-e8f304e2-21f6-45ca-9487-f74b35206165.png)](https://www.reddit.com/r/yakshalang/)
[![github-discuss](https://user-images.githubusercontent.com/498642/229309558-4a1cf297-34f5-47a0-a02d-4881c65aef02.png)](https://github.com/orgs/YakshaLang/discussions)
[![discord](https://user-images.githubusercontent.com/498642/229309839-87739d82-150d-482a-9c7b-6a9ee34808d9.png)](https://discord.gg/SUsJu4PnwU)
[![twitch](https://user-images.githubusercontent.com/498642/229309829-46a32b8c-13e2-437a-bfe9-fb19d52a4410.png)](https://www.twitch.tv/jadoggx86)



## Overview

Welcome to Yaksha an offside-rule based language (Python inspired) that compiles to C99 with Lisp based macros.


## Examples

### Offside Rule (Python inspired) Syntax

```python
# Example Yaksha Code
def main() -> int:
    println("Hello World")
    return 0
```

```python
# return can be omitted
def main() -> int: 0
```

### Compile time macros (YakshaLisp)

```python
# ╔═╗┌─┐┌┬┐┌─┐┬┬  ┌─┐  ╔╦╗┬┌┬┐┌─┐
# ║  │ ││││├─┘││  ├┤    ║ ││││├┤
# ╚═╝└─┘┴ ┴┴  ┴┴─┘└─┘   ╩ ┴┴ ┴└─┘
# ╔═╗┬┌─┐┌─┐  ╔╗ ┬ ┬┌─┐┌─┐
# ╠╣ │┌─┘┌─┘  ╠╩╗│ │┌─┘┌─┘
# ╚  ┴└─┘└─┘  ╚═╝└─┘└─┘└─┘
macros!{
    (defun to_fb (n) (+ (if (== n 1) "" " ") (cond
        ((== 0 (modulo n 15)) "FizzBuzz")
        ((== 0 (modulo n 3)) "Fizz")
        ((== 0 (modulo n 5)) "Buzz")
        (true (to_string n))
        )))
    (defun fizzbuzz () (list (yk_create_token YK_TOKEN_STRING (reduce + (map to_fb (range 1 101))))))
    (yk_register {dsl fizzbuzz fizzbuzz})
}

def main() -> int:
    println(fizzbuzz!{})
    0
```


## Key Features

- **Python like Syntax**: The language syntax is reminiscent of Python, making it accessible and easy to learn for developers familiar with Python and C.

- **Compilation to C99**: Yaksha compiles to C99, enabling efficient execution. Has support for full threads. (No such a thing as GIL).

- **WebAssembly Support**: The compiled code can be further transformed into WebAssembly, allowing Yaksha programs to run seamlessly in web browsers. (Just enable emascipten shell and run `yaksha build`)

- **Lisp-based Macros**: Dive into advanced meta programming with a Lisp-based macro language, offering powerful tools for zero-cost abstraction and code generation. (There are metamacros too!, allowing you to write macros in YakshaLisp to be used at YakshaLisp level)

- **Raylib Integration**: Yaksha integrates with the Raylib game development library, enabling developers to create games with ease.

- **WASM4 Fantasy Console Integration**: Yaksha provides library support for the WASM4 fantasy console, allowing developers to create games for the WASM4 fantasy console. (You just need w4 binary in PATH)

- **IntelliJ/Notepad++/VsCode Support**: Yaksha provides syntax highlighting support for the IntelliJ, Notepad++, and VsCode editors. (Just grab it from release)
  - IntelliJ is more feature rich. 🎉 (Supports goto definition, find usages, etc)
  ![auto-complete](https://raw.githubusercontent.com/YakshaLang/Yaksha/91683551ea1332b772a00a54c8fa1ca4700d00ff/editor/intellij/screenshots/AutoComplete.gif)


- **Cross Platform**: Yaksha is cross-platform, works on Windows, Linux, and macOS ( 🟠 macOS is work in progress, installer is not yet provided). You can even cross compile to WASM (using Emscripten) on Linux / Windows for browser execution. Yaksha bundles `zig` compiler (use `zig cc`) for cross compilation, allowing you to compile multiple targets from a single machine.

- **Playground is a full Debian x86 VM running in browser**: Yaksha playground is a full linux terminal with all the tools you need to develop Yaksha programs. (https://yaksha.pages.dev/)

- **Static binaries**: Yaksha provides static binaries for Linux (musl) (Using `zig cc`).

- **Hot reloading (raylib games/apps)** - (🟠 Currently only works in Windows)


## Why Yaksha?

- **Web Apps**: The seamless integration with WebAssembly makes Yaksha an excellent choice for browser-based applications.

- **Mini Game Development**: The Raylib integration and WASM4 fantasy console support make Yaksha a great choice for game development.

- **Console Applications**: Yaksha is a great choice for console applications, providing a simple and efficient language for developing command-line tools. (Library is cross-platform, so you can use it to develop cross-platform console applications).

- **Meta Programming**: The Lisp-based macro language facilitates advanced meta programming, empowering developers with expressive code generation capabilities. You can do lot in compile time without going into madness of things like template meta programming (in C++) or `#define` macros. You can even use meta-macros to write macros in YakshaLisp to be used at YakshaLisp level. (YakshaLisp is a garbage-collected language unlike Yaksha).

- **New Philosophy**: Yaksha is a new language with a new philosophy. Yaksha use offside rule (Python inspired) syntax, and at the same time we use a Lisp based macro system. I think these two things complement each other very well.
    - **In other words** - Allowing us to explore dualism and harmony of opposites in a programming language. 🧠🤯

## Why not Yaksha?

- **Yaksha is not Python**: Although Yaksha's syntax is inspired by Python, it is not a Python clone. The language is designed to be familiar to Python developers, but it is not a drop-in replacement for Python (and never will be).
- **Yaksha is not a scripting language**: Yaksha is a compiled language, not a scripting language. It is designed to be compiled to C. It is not intended to be interpreted. However, YakshaLisp can be used as a scripting language (`yaksha lisp script.lsp`).
- **Yaksha is not Rust**: Yaksha compiles to C, and it does not provide compile time safety checks like Rust. However, it is heavily type-checked during compile time (may have bugs at the infancy of the language). Additionally `defer` is supported for much simpler resource management. 
- **Yaksha is not a Lisp**: Yaksha is not a Lisp, but it does provide a Lisp-based macro language for meta programming.
- **Yaksha is not a mature language (🟠 Yet)**: Yaksha is still in its infancy. It is not yet ready for production use. (If you fancy a challenge, feel free to try it out!)
- **Yaksha is not Object-Oriented (🟠 Yet)**: Yaksha is not an object-oriented language. It is procedural programming language with a Lisp-based macro language for meta programming.
- **DLL/So/Dylib or static library creation is not supported (🟠 Yet)**: This maybe available in future. Currently, you can only create executables.
- You are allergic to indentation based syntax, Lisp, C(99) or meta programming.
- Logo is too scary for you.


## Getting Started

To explore the language and its capabilities, refer to the [Yaksha Documentation](https://yakshalang.github.io/documentation). This comprehensive guide covers the philosophy, syntax, and features of Yaksha.

## Demos

Check out the fun demos showcasing Yaksha's capabilities: 😺

- [Fractal Tree Demo](https://yakshalang.github.io/static_demos/tree/wind_tree.html): Experience Yaksha compiled to WebAssembly running in the browser.

- [Space Blast Demo](https://yakshalang.github.io/static_demos/space_blast/space_blast.html): Have fun with a space-themed game.

## Contribution

We welcome contributions and feedback. Please use [GitHub Issues](https://github.com/YakshaLang/Yaksha/issues) for bug reports, feature requests, and head to discord for discussions. If you prefer forums you can use GitHub discussions.


---------
```text
 ==============================================================================================
 ╦  ┬┌─┐┌─┐┌┐┌┌─┐┌─┐    Yaksha Programming Language
 ║  ││  ├┤ │││└─┐├┤     is Licensed with GPLv3 + extra terms. Please see below.
 ╩═╝┴└─┘└─┘┘└┘└─┘└─┘
 Note: libs - MIT license, runtime/3rd - various
 ==============================================================================================
 GPLv3:

 Yaksha - Programming Language.
 Copyright (C) 2020 - 2024 Bhathiya Perera

 This program is free software: you can redistribute it and/or modify it under the terms
 of the GNU General Public License as published by the Free Software Foundation,
 either version 3 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with this program.
 If not, see https://www.gnu.org/licenses/.

 ==============================================================================================
 Additional Terms:

 Please note that any commercial use of the programming language's compiler source code
 (everything except compiler/runtime, compiler/libs and compiler/3rd) require a written agreement
 with author of the language (Bhathiya Perera).

 If you are using it for an open source project, please give credits.
 Your own project must use GPLv3 license with these additional terms.

 You may use programs written in Yaksha/YakshaLisp for any legal purpose
 (commercial, open-source, closed-source, etc) as long as it agrees
 to the licenses of linked runtime libraries (see compiler/runtime/README.md).

 ==============================================================================================
```
