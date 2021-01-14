# ARM Emulator

![CI
status](https://github.com/thomasebsmith/arm-emulator/workflows/CI/badge.svg)

This is a lightweight ARM emulator written in cross-platform C++.
Incidentally, this project also includes an ARM disassembler; however,
the disassembler is not the primary focus of this project.

## Build Prerequisites
 - GNU Make
 - `g++` or an equivalent (e.g. Clang) that supports C++17 and the `-MMD` flag

Notes:
 - You can manually build this project without GNU Make and with a
   different C++ compiler by compiling each `.cpp` file to a corresponding `.o`
   file and then linking all the `.o` files from `src/` with the `.o` files in
   either `main/` subdirectory.
 - `g++` should be version 8.0 or later to avoid incorrect compiler warnings
   related to structured bindings.

## Quick Start
```sh
$ git clone https://github.com/thomasebsmith/arm-emulator.git
$ cd arm-emulator/
$ make release
$ ./build/release/disassembler <args>
$ ./build/release/emulator <args>
```

## License
This project is licensed under the MIT license. See [LICENSE](./LICENSE) for
more details.
