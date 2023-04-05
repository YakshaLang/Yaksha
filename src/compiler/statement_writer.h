// statement_writer.h
#ifndef STATEMENT_WRITER_H
#define STATEMENT_WRITER_H
#include <string>
namespace yaksha {
  struct statement_writer {
    virtual ~statement_writer() = default;
    virtual std::string temp() = 0;
    virtual std::string temp(const std::string &custom_prefix) = 0;
    virtual void indent() = 0;
    virtual void dedent() = 0;
    virtual void write_statement(std::string code) = 0;
    virtual void write_statement_no_end(std::string code) = 0;
  };
}// namespace yaksha
#endif
