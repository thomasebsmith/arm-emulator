# ARM Emulator
This is a lightweight ARM emulator written in cross-platform C++.
Incidentally, this project also includes an ARM disassembler; however,
the disassembler is not designed to produce human-friendly output.

## Prerequisites
 - GNU Make
 - `g++` or an equivalent (e.g. Clang) that supports C++17

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
