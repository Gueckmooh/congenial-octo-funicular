#pragma once

#include <memory>

#include "tree_sitter/api.h"

namespace grammar::ts {

class Tree;

class Parser {
  public:
    Parser();

    Tree parse(const std::string& code);

  private:
    std::shared_ptr<TSParser> m_tsParser;
};

} // namespace grammar::ts
