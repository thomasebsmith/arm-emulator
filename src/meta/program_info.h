#ifndef SRC_META_PROGRAM_INFO_H
#define SRC_META_PROGRAM_INFO_H

#include <iostream>
#include <string>

namespace Meta {
  class ProgramInfo {
  public:
    /*
     * Prints information about this project (copyright, version info,
     * etc.) to out. The information is neutral and can be used for
     * either the emulator executable or the disassembler executable.
     */
    static std::ostream &show_version_info(std::ostream &out);
  private:
    static std::string name;
    static std::string version;
    static std::string author;
    static std::string copyright;
    static std::string license;
  };
}

#endif
