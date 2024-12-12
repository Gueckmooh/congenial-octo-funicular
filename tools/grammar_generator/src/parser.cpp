#include "parser.hpp"

#include <string>

#include "utils.hpp"
#include "tree.hpp"

#include "../tree-sitter-grammar/bindings/c/tree-sitter-grammar.h"

namespace grammar::ts {


Parser::Parser()
    : m_tsParser(ts_parser_new(), detail::TSDeleter{}) {
    ts_parser_set_language(m_tsParser.get(), tree_sitter_grammar());
}

Tree Parser::parse(const std::string& code) {
    auto tree = ts_parser_parse_string(m_tsParser.get(), nullptr, code.c_str(),
                                       static_cast<uint32_t>(code.length()));
    return Tree{tree, std::make_shared<std::string>(code)};
}

} // namespace grammar::ts
