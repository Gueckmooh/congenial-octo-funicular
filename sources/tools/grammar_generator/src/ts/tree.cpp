#include "tree.hpp"
#include <memory>
#include "node.hpp"

#include "utils.hpp"

namespace grammar::ts {

Tree::Tree(TSTree* tree, std::shared_ptr<std::string> source)
    : m_tree(tree, detail::TSDeleter{})
    , m_source(std::move(source)) {}

Node Tree::root() {
    return Node{ts_tree_root_node(m_tree.get()), m_source};
}

} // namespace grammar::ts
