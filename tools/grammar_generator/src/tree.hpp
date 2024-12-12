#pragma once

#include <memory>

#include "tree_sitter/api.h"

namespace grammar::ts {

class Node;

class Tree {
    friend class Parser;

  private:
    Tree(TSTree* tree, std::shared_ptr<std::string> source);

  public:
    Node root();

  private:
    std::shared_ptr<TSTree> m_tree;
    std::shared_ptr<std::string> m_source;
};

} // namespace grammar::ts
