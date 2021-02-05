# ARM Emulator

![CI
status](https://github.com/thomasebsmith/arm-emulator/workflows/CI/badge.svg)

This project is a lightweight ARM emulator written in cross-platform C++.
This project also includes an ARM disassembler; however,
the disassembler is not the main focus of this project.

Since this is an emulator and not a compiler (JIT or otherwise), this project
is not particularly fast.

## Build Prerequisites
 - GNU Make
 - `g++` or an equivalent (e.g. Clang) that supports C++17 and the `-MMD` flag
   - The equivalent must be aliased as `g++`.

Notes:
 - You can manually build this project without GNU Make and with a
   different C++ compiler by compiling each `.cpp` file to a corresponding `.o`
   file and then linking all the `.o` files from `src/` with the `.o` files in
   either `main/` subdirectory.
   - Since this project is written in C++17, the compiler will still need to
     support all or many C++17 features.
 - `g++` should be version 8.0 or later to avoid incorrect compiler warnings
   related to structured bindings.

## Quick Start
```sh
$ git clone https://github.com/thomasebsmith/arm-emulator.git
$ cd arm-emulator/
$ make all
$ ./build/debug/test
$ ./build/release/disassembler <args>
$ ./build/release/emulator <args>
```

## Issues
If you find a bug in this program or if you have a feature suggestion, create
a GitHub issue
[here](https://github.com/thomasebsmith/arm-emulator/issues/new).

## License
This project is licensed under the MIT license. See [LICENSE](./LICENSE) for
more details.
