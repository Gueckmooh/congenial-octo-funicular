#include "grammar.hpp"

namespace grammar {



Symbol::Symbol(std::string name)
    : m_name(std::move(name)) {}
std::string_view Symbol::getName() const {
    return m_name;
}

void Terminal::print(std::ostream& os, std::size_t depth) const {
    os << std::string(depth * 4, ' ') << "terminal " << m_name << ";";
}

void Grammar::addTerminal(TerminalPtr terminal) {
    m_terminals.emplace_back(std::move(terminal));
}

void Grammar::addRule(RulePtr rule) {
    m_rules.emplace_back(std::move(rule));
}

const std::vector<TerminalPtr>& Grammar::getTerminals() const {
    return m_terminals;
}

const std::vector<RulePtr>& Grammar::getRules() const {
    return m_rules;
}

void Grammar::print(std::ostream& os, std::size_t depth) const {
    os << std::string(depth * 4, ' ') << "Grammar {\n";
    os << std::string((depth + 1) * 4, ' ') << "/* terminals */\n";
    for (const auto& terminal : m_terminals) {
        terminal->print(os, depth + 1);
        os << '\n';
    }
    os << '\n';
    os << std::string((depth + 1) * 4, ' ') << "/* rules */\n";
    for (const auto& rule : m_rules) {
        rule->print(os, depth + 1);
        os << '\n';
    }
    os << std::string(depth * 4, ' ') << "}";
}

} // namespace grammar
