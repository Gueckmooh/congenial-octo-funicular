#pragma once

#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <unordered_map>

#include "crafting_interpreters/utilities/printable.hpp"

namespace grammar {

class Symbol : public tlox::details::Printable<Symbol> {
  public:
    Symbol(std::string name);
    virtual ~Symbol() = default;

    std::string_view getName() const;

    virtual bool isTerminal() const {
        return false;
    }
    virtual bool isRule() const {
        return false;
    }

    virtual void print(std::ostream& os, std::size_t depth = 0) const = 0;

  protected:
    std::string m_name;
};

class Terminal final : public Symbol {
  public:
    using Symbol::Symbol;

    bool isTerminal() const final {
        return true;
    }

    void print(std::ostream& os, std::size_t depth = 0) const override;
};

class Rule final : public Symbol {
  public:
    using Symbol::Symbol;

    class Element;
    class ElementCollection;
    class Choice;
    class Sequence;
    class SymbolRef;
    class Field;

    void print(std::ostream& os, std::size_t depth = 0) const override;

    bool isRule() const final {
        return true;
    }

    std::shared_ptr<Element> m_body;
    std::vector<std::shared_ptr<Field>> m_fields;
};

class Rule::Element : public tlox::details::Printable<Element> {
  public:
    virtual ~Element() = default;

    std::optional<std::reference_wrapper<Field>> m_maybeField;

    virtual void print(std::ostream& os, std::size_t depth = 0) const = 0;
    virtual bool isElementCollection() const;
    virtual bool isChoice() const;
    virtual bool isSequence() const;
    virtual bool isSymbolRef() const;
};

class Rule::ElementCollection : public Element {
  public:
    bool isElementCollection() const final;
    std::vector<std::shared_ptr<Element>>& elements();
    const std::vector<std::shared_ptr<Element>>& elements() const;

    std::vector<std::shared_ptr<Element>> m_elts;
};

class Rule::Choice final : public ElementCollection {
  public:
    void print(std::ostream& os, std::size_t depth = 0) const override;
    bool isChoice() const final;
};

class Rule::Sequence final : public ElementCollection {
  public:
    void print(std::ostream& os, std::size_t depth = 0) const override;
    bool isSequence() const final;
};

class Rule::SymbolRef final : public Element {
  public:
    void print(std::ostream& os, std::size_t depth = 0) const override;

    bool isSymbolRef() const final;

    std::string m_name;
};

class Rule::Field : public tlox::details::Printable<Field> {
  public:
    std::string m_name;
    std::shared_ptr<Element> m_value;

    void print(std::ostream& os, std::size_t depth = 0) const;
};

using TerminalPtr = std::shared_ptr<Terminal>;
using RulePtr = std::shared_ptr<Rule>;
using SymbolPtr = std::shared_ptr<Symbol>;

class Grammar : public tlox::details::Printable<Grammar> {
  public:
    void addTerminal(TerminalPtr terminal);
    void addRule(RulePtr rule);

    const std::vector<TerminalPtr>& getTerminals() const;
    const std::vector<RulePtr>& getRules() const;

    void print(std::ostream& os, std::size_t depth = 0) const;

    std::optional<SymbolPtr> lookupSymbol(const std::string& name) const;

  private:
    std::vector<TerminalPtr> m_terminals;
    std::vector<RulePtr> m_rules;
    std::unordered_map<std::string, SymbolPtr> m_symbols;
};

} // namespace grammar
