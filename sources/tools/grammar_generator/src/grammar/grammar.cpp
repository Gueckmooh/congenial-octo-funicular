#include "grammar.hpp"

namespace grammar {

// =============================================================================
// Symbol

Symbol::Symbol(std::string name)
    : m_name(std::move(name)) {}
std::string_view Symbol::getName() const {
    return m_name;
}

// =============================================================================
// Terminal

void Terminal::print(std::ostream& os, std::size_t depth) const {
    os << std::string(depth * 4, ' ') << "terminal " << m_name << ";";
}

// =============================================================================
// Rule

void Rule::print(std::ostream& os, std::size_t depth) const {
    os << std::string(depth * 4, ' ') << "Rule " << m_name << "{\n";
    os << std::string(depth * 4, ' ') << "    " << *m_body << '\n';
    for (const auto& field : m_fields) {
        os << std::string(depth * 4, ' ') << "    field: " << *field << '\n';
    }
    os << std::string(depth * 4, ' ') << "}";
}

// =============================================================================
// Rule::Element

bool Rule::Element::isElementCollection() const {
    return false;
}
bool Rule::Element::isChoice() const {
    return false;
}
bool Rule::Element::isSequence() const {
    return false;
}
bool Rule::Element::isSymbolRef() const {
    return false;
}

// =============================================================================
// Rule::ElementCollection

bool Rule::ElementCollection::isElementCollection() const {
    return true;
}
std::vector<std::shared_ptr<Rule::Element>>& Rule::ElementCollection::elements() {
    return m_elts;
}

const std::vector<std::shared_ptr<Rule::Element>>& Rule::ElementCollection::elements() const {
    return m_elts;
}

// =============================================================================
// Rule::Choice

void Rule::Choice::print(std::ostream& os, std::size_t depth) const {
    os << std::string(depth * 4, ' ') << '(';
    for (std::size_t idx = 0; idx < m_elts.size(); ++idx) {
        os << *m_elts.at(idx);
        if (idx < m_elts.size() - 1) {
            os << " | ";
        }
    }
    os << ')';
}
bool Rule::Choice::isChoice() const {
    return true;
}

// =============================================================================
// Rule::Sequence

void Rule::Sequence::print(std::ostream& os, std::size_t depth) const {
    os << std::string(depth * 4, ' ') << '(';
    for (std::size_t idx = 0; idx < m_elts.size(); ++idx) {
        os << *m_elts.at(idx);
        if (idx < m_elts.size() - 1) {
            os << " ";
        }
    }
    os << ')';
}

bool Rule::Sequence::isSequence() const {
    return true;
}

// =============================================================================
// Rule::SymbolRef

void Rule::SymbolRef::print(std::ostream& os, std::size_t depth) const {
    os << std::string(depth * 4, ' ') << m_name;
}

bool Rule::SymbolRef::isSymbolRef() const {
    return true;
}
// =============================================================================
// Rule::Field

void Rule::Field::print(std::ostream& os, std::size_t depth) const {
    os << std::string(depth * 4, ' ') << m_name << " = " << *m_value;
}

// =============================================================================
// Grammar

void Grammar::addTerminal(TerminalPtr terminal) {
    m_symbols.emplace(std::string(terminal->getName()), terminal);
    m_terminals.emplace_back(std::move(terminal));
}

void Grammar::addRule(RulePtr rule) {
    m_symbols.emplace(std::string(rule->getName()), rule);
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

std::optional<SymbolPtr> Grammar::lookupSymbol(const std::string& name) const {
    if (auto it = m_symbols.find(name); it != m_symbols.end()) {
        return it->second;
    }
    return {};
}

} // namespace grammar
