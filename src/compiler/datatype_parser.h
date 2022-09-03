// datatype_parser.h
#ifndef DATATYPE_PARSER_H
#define DATATYPE_PARSER_H
#include "utilities/ykdatatype.h"
#include <string>
#include <unordered_map>
namespace yaksha {
  struct datatype_parser {
    virtual ~datatype_parser() = default;
    virtual ykdatatype *
    parse(std::string data_type_str,
          const std::unordered_map<std::string, import_stmt *> &import_aliases,
          const std::string &filepath) = 0;
  };
}// namespace yaksha
#endif
