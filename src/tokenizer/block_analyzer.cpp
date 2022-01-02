// indent_analyzer.cpp
#include "tokenizer/block_analyzer.h"
#include <algorithm>
#include <cassert>
#include <utf8.h>
using namespace yaksha;
/**
 * @param possibly_open
 * @return is one of ( [ {
 */
inline bool is_open_bracket(token_type possibly_open) {
  return (possibly_open == token_type::PAREN_OPEN ||
          possibly_open == token_type::SQUARE_BRACKET_OPEN ||
          possibly_open == token_type::CURLY_BRACKET_OPEN);
}
/**
 * @param possibly_open
 * @return is one of } ] )
 */
inline bool is_close_bracket(token_type possibly_open) {
  return (possibly_open == token_type::PAREN_CLOSE ||
          possibly_open == token_type::SQUARE_BRACKET_CLOSE ||
          possibly_open == token_type::CURLY_BRACKET_CLOSE);
}
/**
 * Are the two parens matching?
 * @param open opening bracket - must be an open bracket
 * @param close closing bracket - must be a close bracket
 * @return if opening bracket and closing is of same type - () [] {}
 */
inline bool is_bracket_matching(yaksha::token_type open,
                                yaksha::token_type close) {
  return (is_open_bracket(open) && is_close_bracket(close)) &&
         ((open == token_type::PAREN_OPEN &&
           close == token_type::PAREN_CLOSE) ||
          (open == token_type::SQUARE_BRACKET_OPEN &&
           close == token_type::SQUARE_BRACKET_CLOSE) ||
          (open == token_type::CURLY_BRACKET_OPEN &&
           close == token_type::CURLY_BRACKET_CLOSE));
}
bool strict_indent_check(const token &t, indent_type type) {
  if (t.type_ != token_type::INDENT) { return true; }
  auto indent_len = t.token_.length();
  if (type == indent_type::TWO_SPACES && indent_len % 2 != 0) { return false; }
  if (type == indent_type::FOUR_SPACES && indent_len % 4 != 0) { return false; }
  auto character = (type == indent_type::TAB) ? '\t' : ' ';
  auto begin = t.token_.begin();
  auto end = t.token_.end();
  // indentation of size 0 is not there
  while (begin != end) {
    auto c = utf8::next(begin, end);
    if (c != character) { return false; }
  }
  return true;
}
std::size_t indent_to_level(const std::string &indent, indent_type type) {
  if (type == indent_type::TAB) { return indent.length(); }
  if (type == indent_type::TWO_SPACES) { return indent.length() / 2; }
  return indent.length() / 4;
}
std::size_t guess_indent_level(std::size_t previous_indent, indent_type type,
                               const token &t) {
  std::size_t spaces = 0;
  std::size_t tabs = 0;
  auto begin = t.token_.begin();
  auto end = t.token_.end();
  // indentation of size 0 is not there
  while (begin != end) {
    auto c = utf8::next(begin, end);
    // note that we can only have spaces and tabs in indentation
    if (c == ' ') {
      spaces++;
    } else {
      tabs++;
    }
  }
  if (type == yaksha::indent_type::TAB) {
    tabs += spaces / 2;
  } else {
    spaces += tabs * 4;
  }
  if (type == yaksha::indent_type::TWO_SPACES) {
    spaces /= 2;
  } else if (type == yaksha::indent_type::FOUR_SPACES) {
    spaces /= 4;
  }
  std::size_t possible_size =
      (type == yaksha::indent_type::TAB) ? tabs : spaces;
  if (possible_size > previous_indent) {
    return previous_indent + 1;
  } else if (possible_size < previous_indent) {
    return previous_indent - 1;
  }
  return previous_indent;
}
block_analyzer::block_analyzer(const std::vector<token> &tokens)
    : tokens_(), original_tokens_(tokens), errors_() {}
void block_analyzer::analyze() {
  if (original_tokens_.empty()) { return; }
  std::vector<token_type> brackets{};
  std::vector<std::size_t> indents{};
  std::vector<token> cleaned{}; /** Without COMMENTS and extra lines */
  brackets.reserve(50);
  indents.reserve(50);
  cleaned.reserve(original_tokens_.size());
  tokens_.reserve(original_tokens_.size());
  auto iterator = original_tokens_.begin();
  auto end = original_tokens_.end();
  // clean up comments and extra new lines
  while (iterator != end) {
    auto tok = *iterator;
    iterator++;
    if (tok.type_ == token_type::COMMENT) {
      continue;
    } else if (tok.type_ == token_type::NEW_LINE) {
      // Don't start with new lines, Don't add a newline after a new line
      if (cleaned.empty() || cleaned.back().type_ == token_type::NEW_LINE) {
        continue;
      } else if (cleaned.back().type_ == token_type::INDENT) {
        // get rid of empty indents that just follows by a new line
        cleaned.pop_back();
      }
    }
    cleaned.emplace_back(tok);
  }
  indent_type allowed_indent_type = indent_type::UNKNOWN;
  // iterate cleaned to capture indent/dedent blocks
  iterator = cleaned.begin();
  end = cleaned.end();
  bool inside_bracket_block = false;
  while (iterator != end) {
    auto tok = *iterator;
    iterator++;
    if (is_open_bracket(tok.type_)) {
      brackets.push_back(tok.type_);
      inside_bracket_block = !brackets.empty();
    } else if (is_close_bracket(tok.type_)) {
      if (brackets.empty()) {
        handle_error(parsing_error("BlockAnalyzer Error"
                                   " : Unmatched closing bracket",
                                   tok.file_, tok.line_, tok.pos_));
        continue;
      } else if (!is_bracket_matching(brackets.back(), tok.type_)) {
        handle_error(parsing_error("BlockAnalyzer Error"
                                   " : Incorrect closing bracket",
                                   tok.file_, tok.line_, tok.pos_));
        continue;
      }
      brackets.pop_back();
      inside_bracket_block = !brackets.empty();
    } else if (tok.type_ == token_type::INDENT) {
      if (inside_bracket_block) {// special case when multi line {a: []} data
        continue;
      }
      // based on first indent determine allowed indent
      // TODO would be better to look at all the indents and then determine
      // which has the higher probability
      bool ignored_error = false;
      if (allowed_indent_type == indent_type::UNKNOWN) {
        allowed_indent_type = str_to_indent_type(tok.token_);
        if (allowed_indent_type == indent_type::UNKNOWN) {
          handle_error(parsing_error("BlockAnalyzer Error"
                                     " : First indent of this file invalid,"
                                     " assuming 4 spaces are used.",
                                     tok.file_, tok.line_, tok.pos_));
          allowed_indent_type = indent_type::FOUR_SPACES;
          ignored_error = true;
        }
      }
      if (!ignored_error && !strict_indent_check(tok, allowed_indent_type)) {
        handle_error(parsing_error("BlockAnalyzer Error : Invalid indentation",
                                   tok.file_, tok.line_, tok.pos_));
        ignored_error = true;
      }
      std::size_t previous_level = indents.empty() ? 0 : indents.back();
      std::size_t current_level =
          ignored_error
              ? guess_indent_level(previous_level, allowed_indent_type, tok)
              : indent_to_level(tok.token_, allowed_indent_type);
      if (indents.empty()) {
        tokens_.emplace_back(
            token{tok.file_, tok.line_, tok.pos_, "", token_type::BA_INDENT});
      } else {
        auto prev_level = indents.back();
        if (prev_level > current_level) {// dedent
          create_dedents(indents, tok, prev_level, current_level);
        } else if (prev_level < current_level) {// indent
          if (current_level - prev_level != 1) {
            handle_error(parsing_error("BlockAnalyzer Error"
                                       " : Too much indentation",
                                       tok.file_, tok.line_, tok.pos_));
          }
          indents.pop_back();
          tokens_.emplace_back(
              token{tok.file_, tok.line_, tok.pos_, "", token_type::BA_INDENT});
        } else {// same size indents doesn't start a block
          continue;
        }
      }
      indents.push_back(current_level);
      continue;
    } else if (tok.type_ == token_type::NEW_LINE) {
      if (inside_bracket_block || tokens_.empty() ||
          tokens_.back().type_ == token_type::BA_DEDENT) {
        continue;
      }
      if (iterator != end && iterator->type_ != token_type::INDENT) {
        std::size_t prev_level = indents.empty() ? 0 : indents.back();
        std::size_t current_level = 0;
        if (prev_level > current_level) {// dedent
          tokens_.emplace_back(tok);
          create_dedents(indents, tok, prev_level, current_level);
        } else {
          tokens_.emplace_back(tok);
        }
        continue;
      }
    } else if (tok.type_ == token_type::END_OF_FILE) {
      // dedent to level 0
      std::size_t prev_level = indents.empty() ? 0 : indents.back();
      std::size_t current_level = 0;
      if (prev_level > current_level) {// dedent
        create_dedents(indents, tok, prev_level, current_level);
      }
    }
    tokens_.emplace_back(tok);
  }
}
void block_analyzer::create_dedents(std::vector<std::size_t> &indents,
                                    const token &tok, size_t prev_level,
                                    size_t current_level) {
  // prev_level must be > current_level
  indents.pop_back();
  // we may dedent more than 1 level at one go
  std::size_t dedent_count = prev_level - current_level;
  for (std::size_t x = 0; x < dedent_count; x++) {
    tokens_.emplace_back(
        token{tok.file_, tok.line_, tok.pos_, "", token_type::BA_DEDENT});
  }
}
void block_analyzer::handle_error(const parsing_error &err) {
  errors_.emplace_back(err);
}
