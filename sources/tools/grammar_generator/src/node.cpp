#include "node.hpp"
#include <cstdint>
#include <string_view>
#include "tree_sitter/api.h"

namespace grammar::ts {

Node::Node(TSNode node, std::shared_ptr<std::string> source)
    : m_node(std::move(node))
    , m_source(std::move(source)) {}

std::string Node::string() const {
    auto c = ts_node_string(m_node);
    std::string s{c};
    std::free(c);
    return s;
}

std::string Node::value() const {
    return std::string{m_source->begin() + ts_node_start_byte(m_node),
                       m_source->begin() + ts_node_end_byte(m_node)};
}

std::string Node::type() const {
    auto c = ts_node_type(m_node);
    std::string s{c};
    return s;
}

std::vector<Node> Node::children(bool onlyNamed) const {
    std::vector<Node> nodes;
    if (onlyNamed) {
        for (uint32_t idx = 0; idx < ts_node_named_child_count(m_node); ++idx) {
            nodes.emplace_back(ts_node_named_child(m_node, idx), m_source);
        }
    } else {
        for (uint32_t idx = 0; idx < ts_node_child_count(m_node); ++idx) {
            nodes.emplace_back(ts_node_child(m_node, idx), m_source);
        }
    }
    return nodes;
}

std::vector<Node> Node::children(const char* name) const {
    return children(std::string_view(name));
}

std::vector<Node> Node::children(std::string_view name) const {
    std::vector<Node> nodes;
    for (uint32_t idx = 0; idx < ts_node_named_child_count(m_node); ++idx) {
        auto tsNode = ts_node_named_child(m_node, idx);
        if (std::string_view(ts_node_type(tsNode)) != name) {
            continue;
        }
        nodes.emplace_back(tsNode, m_source);
    }
    return nodes;
}

std::optional<Node> Node::child(std::string_view name, bool mustBeNamed) const {
    auto tsNode =
        ts_node_child_by_field_name(m_node, name.data(), static_cast<uint32_t>(name.length()));
    while (mustBeNamed && !ts_node_is_null(tsNode) && !ts_node_is_named(tsNode)) {
        tsNode = ts_node_next_named_sibling(tsNode);
    }
    if (ts_node_is_null(tsNode)) {
        return std::nullopt;
    }
    return Node{tsNode, m_source};
}

bool Node::isNamed() const {
    return ts_node_is_named(m_node);
}

} // namespace grammar::ts
