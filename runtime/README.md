# Yaksha Runtime

Bunch of `C` code that standard library depend on.

## Third Party Libraries

| files           | author                              | use                                | repo                                                      | license                                                                                |
|-----------------|-------------------------------------|------------------------------------|-----------------------------------------------------------|----------------------------------------------------------------------------------------|
| `ini.h`         | Mattias Gustavsson and contributors | work with .ini files               | [libs](https://github.com/mattiasgustavsson/libs)         | MIT/PublicDomain                                                                       |
| `subprocess.h`  | sheredom and contributors           | Subprocess support (used for UNIX) | [subprocess.h](https://github.com/sheredom/subprocess.h)  | Unlicense                                                                              |
| `toml.*`        | CK Tan and contributors             | TOML support                       | [tomlc99](https://github.com/cktan/tomlc99)               | MIT                                                                                    |
| `utfproc*`      | various                             | utf8 string iteration support      | [utfproc](https://github.com/JuliaStrings/utf8proc)       | [MIT expat + 2 other](https://github.com/JuliaStrings/utf8proc/blob/master/LICENSE.md) |
| `whereami.*`    | Gregory Pakosz and contributors     | Get exe path                       | [whereami](https://github.com/gpakosz/whereami)           | MIT/WTFPL                                                                              |
| `raylib/*`      | Ramon Santamaria and contributors   | Game/GUI development               | [raylib](https://github.com/raysan5/raylib)               | Zlib                                                                                   |
| `raygui/*`      | Ramon Santamaria and contributors   | Game/GUI development               | [raygui](https://github.com/raysan5/raygui)               | Zlib                                                                                   |
| `argparse.*`    | Yecheng Fu and contributors         | Argument parsing                   | [argparse](https://github.com/cofyc/argparse)             | MIT                                                                                    |
| `tinycthread.*` | Marcus Geelnard, Evan Nemerson      | Thread Library                     | [tinycthread](https://github.com/tinycthread/tinycthread) | [Custom?](https://github.com/tinycthread/tinycthread)                                  |
| `wasm4.h`       | Bruno Garcia                        | wasm4 fantasy console C header     | [wasm4](https://github.com/aduros/wasm4)                  | ISC                                                                                    |

### Patches

* argparse - `const char short_name;` was changed to `char short_name;`
* argparse - added windows support for argparse help printing/error printing.

### Third Party Derived

| files           | use                                                         | original repo(s)                                                                 | license(s)                                     |
|-----------------|-------------------------------------------------------------|----------------------------------------------------------------------------------|------------------------------------------------|
| `yk__console.h` | based on a library by Giovanny Andres Gongora Granada       | [color-sh](https://github.com/Gioyik/color-sh)                                   | MIT                                            |
| `yk__lib.h`     | based on sds library and stb_ds library, custom repackaged. | [sds](https://github.com/antirez/sds), [stb_ds](https://github.com/nothings/stb) | sds is BSD 2 clause, stb_ds - MIT/PublicDomain |

### First Party Code

All other files are first party code.
