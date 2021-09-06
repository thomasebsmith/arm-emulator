# Project Architecture
ARM Emulator has three main categories of source code.

## `main`
A small amount of source code is found in `main/`. `main/` contains files
that create the specific disassembler and emulator command-line interfaces
and executables.

## `src`
Most source code is found in `src/`. `src/` contains all files shared among
the disassembler and emulator, as well as any file that does not directly
relate to one of those two executables.

Here is an overview of the subdirectories of `src/`:
 - `cli`: Contains generic code for parsing command-line arguments. Used by
          both the disassembler and the emulator.
 - `disassemble`: Contains code for converting a stream of bits into a series
          of instructions.
 - `instructions`: Contains all instruction-specific code (disassembling,
          emulating, etc). Generally, there is one .cpp file per instruction
          type. This may be refactored at some point to avoid having too many
          files in one directory.
 - `meta`: Contains code that provides information about the project as a
          whole (e.g. authors, copyright, etc.).
 - `utils`: Contains utility classes and functions. Currently, this only
          contains utilities related to parsing bits.

## `test`
There is also some source code in the form of unit and integration tests in
`test/`.

Here is an overview of the subdirectories of `test/`:
 - `cli`: Contains tests related to command-line interface code.
 - `main`: Contains the main program that runs all the tests.
 - `shared`: Contains types and objects that are used to define tests.
