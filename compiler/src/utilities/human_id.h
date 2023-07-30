// human_id.h
#ifndef HUMAN_ID_H
#define HUMAN_ID_H
#include <string>
namespace yaksha::human_id {
  std::string human_id();
  std::string low_entropy_uuid();
}// namespace yaksha::human_id
#endif
