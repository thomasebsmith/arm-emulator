#include <string>
#include "program_info.h"

std::string Meta::ProgramInfo::name = "ARM Emulator";
std::string Meta::ProgramInfo::version = "0.0";
std::string Meta::ProgramInfo::author = "Thomas Smith";
std::string Meta::ProgramInfo::copyright = "2020";
std::string Meta::ProgramInfo::license = "the MIT License";

std::ostream &Meta::ProgramInfo::show_version_info(std::ostream &out) {
  out << name << " version " << version << '\n';
  out << "Copyright (C) " << copyright << ' ' << author << ".\n";
  out << "Licensed under " << license << ".\n";
  return out;
}
