#ifndef __SRC_META_PROGRAM_INFO_H__
#define __SRC_META_PROGRAM_INFO_H__

#include <iostream>
#include <string>

namespace Meta {
  class ProgramInfo {
  public:
    static std::ostream &show_version_info(std::ostream &out);
  private:
    static std::string name;
    static std::string version;
    static std::string author;
    static std::string copyright;
  };
}

#endif
