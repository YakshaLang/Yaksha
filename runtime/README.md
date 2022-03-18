# Yaksha Runtime

Bunch of `C` code that standard library and main program depend on.

## Third Party Libraries

| files          | author             | use                                |
|----------------|--------------------|------------------------------------|
| `ini.h`        | Mattias Gustavsson | work with .ini files               |
| `subprocess.h` | sheredom           | Subprocess support (used for UNIX) |
| `toml.*`       | CK Tan             | TOML support                       |
| `mpc.*`        | orangeduck         | Text parsing                       |
| `utfproc*`     | various            | utf8 string iteration support      |
| `whereami.*`   | Gregory Pakosz     | Get exe path                       |

### Third Party Derived

| files          | use                                                         |
|----------------|-------------------------------------------------------------|
| `yk__colour.h` | based on a library by Giovanny Andres Gongora Granada       |
| `yk__lib.h`    | based on sds library and stb_ds library, custom repackaged. |

### First Party Code

All other files are first party code.