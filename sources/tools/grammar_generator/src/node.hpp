#pragma once

#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <ostream>

#include "tree_sitter/api.h"

namespace grammar::ts {

class Node {
    friend class Tree;

  public:
    Node(TSNode node, std::shared_ptr<std::string> source);

  public:
    std::string string() const;
    std::string value() const;
    std::string type() const;
    std::vector<Node> children(bool onlyNamed = false) const;
    std::vector<Node> children(const char* name) const;
    std::vector<Node> children(std::string_view name) const;
    std::optional<Node> child(std::string_view name, bool mustBeNamed = true) const;
    bool isNamed() const;

  private:
    TSNode m_node;
    std::shared_ptr<std::string> m_source;
};

inline std::ostream& operator<<(std::ostream& os, const Node& node) {
    return os << node.string();
}

inline void prettyPrint(std::ostream& os, const Node& n, std::size_t d = 0) {
    os << std::string(d * 2, ' ');
    os << n.type() << " '" << n.value() << "'\n";
    for (const auto& c : n.children(true)) {
        prettyPrint(os, c, d + 1);
    }
}

} // namespace grammar::ts
