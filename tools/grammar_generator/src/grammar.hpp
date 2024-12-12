#pragma once

#include <string>
#include <vector>
#include <memory>
#include <optional>

#include "crafting_interpreters/utilities/printable.hpp"

namespace grammar {

class Terminal : public tlox::details::Printable<Terminal> {
  public:
    Terminal(std::string name);

    void print(std::ostream& os, std::size_t depth = 0) const;

    std::string_view getName() const;

  private:
    std::string m_name;
};

class Rule : public tlox::details::Printable<Rule> {
  public:
    Rule(std::string name)
        : m_name(std::move(name)) {}

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

    void print(std::ostream& os, std::size_t depth = 0) const {
        os << std::string(depth * 4, ' ') << "Rule " << m_name << "{\n";
        os << std::string(depth * 4, ' ') << "    " << *m_body << '\n';
        for (const auto& field : m_fields) {
            os << std::string(depth * 4, ' ') << "    field: " << *field << '\n';
        }
        os << std::string(depth * 4, ' ') << "}";
    }

    std::string m_name;
    std::shared_ptr<Element> m_body;
    std::vector<std::shared_ptr<Field>> m_fields;
};

class Grammar : public tlox::details::Printable<Grammar> {
  public:
    void addTerminal(Terminal terminal);
    void addRule(Rule rule);

    const std::vector<Terminal>& getTerminals() const;
    const std::vector<Rule>& getRules() const;

    void print(std::ostream& os, std::size_t depth = 0) const;

  private:
    std::vector<Terminal> m_terminals;
    std::vector<Rule> m_rules;
};

} // namespace grammar
