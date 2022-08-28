# Yaksha Runtime

Bunch of `C` code that standard library and main program depend on.

## Third Party Libraries

| files          | author                              | use                                |
|----------------|-------------------------------------|------------------------------------|
| `ini.h`        | Mattias Gustavsson and contributors | work with .ini files               |
| `subprocess.h` | sheredom and contributors           | Subprocess support (used for UNIX) |
| `toml.*`       | CK Tan and contributors             | TOML support                       |
| `mpc.*`        | orange duck and contributors        | Text parsing                       |
| `utfproc*`     | various                             | utf8 string iteration support      |
| `whereami.*`   | Gregory Pakosz and contributors     | Get exe path                       |
| `raylib/*`     | Ramon Santamaria and contributors   | Game/GUI development               |
| `raygui/*`     | Ramon Santamaria and contributors   | Game/GUI development               |
| `argparse.*`   | Yecheng Fu and contributors         | Argument parsing                   |

### Minor Patches
* argparse - `const char short_name;` was changed to `char short_name;`

### Third Party Derived

| files           | use                                                         |
|-----------------|-------------------------------------------------------------|
| `yk__console.h` | based on a library by Giovanny Andres Gongora Granada       |
| `yk__lib.h`     | based on sds library and stb_ds library, custom repackaged. |

### First Party Code

All other files are first party code.