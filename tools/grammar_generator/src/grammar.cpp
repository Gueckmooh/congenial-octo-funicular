#include "grammar.hpp"

namespace grammar {

Terminal::Terminal(std::string name)
    : m_name(std::move(name)) {}

void Terminal::print(std::ostream& os, std::size_t depth) const {
    os << std::string(depth * 4, ' ') << "terminal " << m_name << ";";
}

std::string_view Terminal::getName() const {
    return m_name;
}

void Grammar::addTerminal(Terminal terminal) {
    m_terminals.emplace_back(std::move(terminal));
}

void Grammar::addRule(Rule rule) {
    m_rules.emplace_back(std::move(rule));
}

const std::vector<Terminal>& Grammar::getTerminals() const {
    return m_terminals;
}

const std::vector<Rule>& Grammar::getRules() const {
    return m_rules;
}

void Grammar::print(std::ostream& os, std::size_t depth) const {
    os << std::string(depth * 4, ' ') << "Grammar {\n";
    os << std::string((depth + 1) * 4, ' ') << "/* terminals */\n";
    for (const auto& terminal : m_terminals) {
        terminal.print(os, depth + 1);
        os << '\n';
    }
    os << '\n';
    os << std::string((depth + 1) * 4, ' ') << "/* rules */\n";
    for (const auto& rule : m_rules) {
        rule.print(os, depth + 1);
        os << '\n';
    }
    os << std::string(depth * 4, ' ') << "}";
}

} // namespace grammar
