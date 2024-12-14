#pragma once

#include <string>
#include <variant>
#include <vector>
#include <memory>
#include <optional>

#include "crafting_interpreters/utilities/printable.hpp"

namespace grammar {

class Symbol : public tlox::details::Printable<Symbol> {
  public:
    Symbol(std::string name);
    virtual ~Symbol() = default;

    std::string_view getName() const;

    virtual void print(std::ostream& os, std::size_t depth = 0) const = 0;

  protected:
    std::string m_name;
};

class Terminal final : public Symbol {
  public:
    using Symbol::Symbol;

    void print(std::ostream& os, std::size_t depth = 0) const override;
};

class Rule final : public Symbol {
  public:
    using Symbol::Symbol;

    class Field;
    class Element : public tlox::details::Printable<Element> {
      public:
        virtual ~Element() = default;

        std::optional<std::reference_wrapper<Field>> m_maybeField;

        virtual void print(std::ostream& os, std::size_t depth = 0) const = 0;
        virtual bool isElementCollection() const {
            return false;
        }
        virtual bool isChoice() const {
            return false;
        }
        virtual bool isSequence() const {
            return false;
        }
        virtual bool isSymbolRef() const {
            return false;
        }
    };

    class ElementCollection : public Element {
      public:
        bool isElementCollection() const final {
            return true;
        }
        std::vector<std::shared_ptr<Element>> m_elts;
        std::vector<std::shared_ptr<Element>>& elements() {
            return m_elts;
        }
    };

    class Choice final : public ElementCollection {
      public:
        void print(std::ostream& os, std::size_t depth = 0) const override {
            os << std::string(depth * 4, ' ') << '(';
            for (std::size_t idx = 0; idx < m_elts.size(); ++idx) {
                os << *m_elts.at(idx);
                if (idx < m_elts.size() - 1) {
                    os << " | ";
                }
            }
            os << ')';
        }
        bool isChoice() const final {
            return true;
        }
    };

    class Sequence final : public ElementCollection {
      public:
        void print(std::ostream& os, std::size_t depth = 0) const override {
            os << std::string(depth * 4, ' ') << '(';
            for (std::size_t idx = 0; idx < m_elts.size(); ++idx) {
                os << *m_elts.at(idx);
                if (idx < m_elts.size() - 1) {
                    os << " ";
                }
            }
            os << ')';
        }

        bool isSequence() const final {
            return true;
        }
    };

    class SymbolRef final : public Element {
      public:
        void print(std::ostream& os, std::size_t depth = 0) const override {
            os << std::string(depth * 4, ' ') << m_name;
        }

        bool isSymbolRef() const final {
            return true;
        }

        std::string m_name;
    };

    class Field : public tlox::details::Printable<Field> {
      public:
        std::string m_name;
        std::shared_ptr<Element> m_value;

        void print(std::ostream& os, std::size_t depth = 0) const {
            os << std::string(depth * 4, ' ') << m_name << " = " << *m_value;
        }
    };

    void print(std::ostream& os, std::size_t depth = 0) const override {
        os << std::string(depth * 4, ' ') << "Rule " << m_name << "{\n";
        os << std::string(depth * 4, ' ') << "    " << *m_body << '\n';
        for (const auto& field : m_fields) {
            os << std::string(depth * 4, ' ') << "    field: " << *field << '\n';
        }
        os << std::string(depth * 4, ' ') << "}";
    }

    std::shared_ptr<Element> m_body;
    std::vector<std::shared_ptr<Field>> m_fields;
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

    // std::variant< std::monostate> lookupSymbol();

  private:
    std::vector<TerminalPtr> m_terminals;
    std::vector<RulePtr> m_rules;
};

} // namespace grammar
