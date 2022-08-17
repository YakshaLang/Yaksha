// entry_struct_compiler.h
#ifndef ENTRY_STRUCT_COMPILER_H
#define ENTRY_STRUCT_COMPILER_H
#include "datatype_compiler.h"
#include "utilities/ykdt_pool.h"
#include <unordered_map>
namespace yaksha {
  struct entry_data {
    ykdatatype* key_dt_;
    ykdatatype* val_dt_;
    unsigned int incremented_id_;
  };
  struct entry_struct_compiler {
    explicit entry_struct_compiler(ykdt_pool *pool);
    std::string compile(ykdatatype* entry_dt, datatype_compiler* dtc);
    void compile_forward_declarations(std::stringstream& target);
    void compile_structures(std::stringstream& target);
    bool has();
    ~entry_struct_compiler();

private:
    ykdt_pool *pool_;
    std::vector<entry_data> autogen_structs_list_;
    std::unordered_map<std::string, unsigned int> autogen_structs_;
    std::stringstream code_;
    unsigned int counter_;
  };
}// namespace yaksha
#endif
