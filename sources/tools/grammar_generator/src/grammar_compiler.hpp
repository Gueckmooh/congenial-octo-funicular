#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <iostream>
#include <string>
#include <cassert>

#include "crafting_interpreters/utilities/printable.hpp"

#include "grammar.hpp"
#include "tree.hpp"
#include "node.hpp"

namespace grammar {

class GrammarCompiler {
  public:
    GrammarCompiler(ts::Tree tree)
        : m_tree(std::move(tree)) {}

    Grammar compile() {
        // Reset the grammar in case we call `compile()` several times
        m_grammar = Grammar{};

        compileTerminals();
        compileRules();

        return m_grammar;
    }

  private:
    void compileTerminals() {
        auto terminalsDefs = m_tree.root().children("terminal_definition");
        for (const auto& terminalDef : terminalsDefs) {
            if (auto res = compileTerminal(terminalDef)) {
                m_grammar.addTerminal(std::move(*res));
            }
        }
    }

    void compileRules() {
        auto rulesDefs = m_tree.root().children("rule_definition");
        for (const auto& ruleDef : rulesDefs) {
            if (auto res = compileRule(ruleDef)) {
                m_grammar.addRule(std::move(*res));
            }
        }
    }

    std::optional<Terminal> compileTerminal(const ts::Node& node) {
        auto symbolNode = node.child("name");
        if (!symbolNode) {
            return std::nullopt;
        }
        return Terminal{symbolNode->value()};
    }

    std::optional<Rule> compileRule(const ts::Node& node) {
        auto maybeNameNode = node.child("name");
        auto maybeBody = node.child("body");
        if (!maybeNameNode || !maybeBody) {
            return {};
        }
        auto name = maybeNameNode->value();

        Rule rule{name};
        rule.m_body = parseRuleElement(*maybeBody, rule);

        return rule;
    }

    std::shared_ptr<Rule::Element> parseRuleElement(const ts::Node& node, Rule& rule) {
        auto type = node.type();
        if (type == "choice") {
            return parseChoice(node, rule);
        } else if (type == "sequence") {
            return parseSequence(node, rule);
        } else if (type == "affectation") {
            return parseAffectation(node, rule);
        } else if (type == "symbol") {
            return parseSymbolRef(node);
        } else {
            std::cerr << "could not parse " << node << std::endl;
            assert(false);
        }

        return {};
    }

    std::shared_ptr<Rule::Element> parseChoice(const ts::Node& node, Rule& rule) {
        auto choice = std::make_shared<Rule::Choice>();
        for (const auto& child : node.children(true)) {
            choice->m_elts.emplace_back(parseRuleElement(child, rule));
        }

        if (choice->elements().size() == 1) {
            return choice->elements().front();
        }

        return choice;
    }
    std::shared_ptr<Rule::Element> parseSequence(const ts::Node& node, Rule& rule) {

        auto choice = std::make_shared<Rule::Sequence>();
        for (const auto& child : node.children(true)) {
            choice->m_elts.emplace_back(parseRuleElement(child, rule));
        }

        if (choice->elements().size() == 1) {
            return choice->elements().front();
        }

        return choice;
    }
    std::shared_ptr<Rule::Element> parseSymbolRef(const ts::Node& node) {
        auto symRef = std::make_shared<Rule::SymbolRef>();
        symRef->m_name = node.value();
        return symRef;
    }
    std::shared_ptr<Rule::Element> parseAffectation(const ts::Node& node, Rule& rule) {
        auto maybeName = node.child("name");
        auto maybeValue = node.child("value");
        if (!maybeName || !maybeValue) {
            return {};
        }

        auto field = std::make_shared<Rule::Field>();
        field->m_name = maybeName->value();

        field->m_value = parseRuleElement(*maybeValue, rule);
        rule.m_fields.push_back(field);

        return field->m_value;
    }

  private:
    ts::Tree m_tree;
    Grammar m_grammar;
};

} // namespace grammar
