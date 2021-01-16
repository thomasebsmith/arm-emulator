#ifndef MAIN_DISASSEMBLER_DISASSEMBLE_H
#define MAIN_DISASSEMBLER_DISASSEMBLE_H

#include <iostream>

/*
 * Disassembles the machine code contained in in, writing output to out.
 * If any errors occur, they are written to out_err and a non-zero exit code
 * is returned.
 */
int disassemble(std::istream &in, std::ostream &out, std::ostream &out_err);

#endif
