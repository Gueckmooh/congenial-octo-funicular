#include "cxx_rule_generator.hpp"

#include <iostream>
#include <cassert>
#include <memory>
#include <set>

#include "type_checker.hpp"

import cpp_generator;

namespace grammar::generator {

class RuleCXXGenerator::Impl {
  public:
    Impl(const Grammar& grammar)
        : m_grammar(grammar) {}

    cpp_generator::ClassBuilder generateClassFromRule(const RulePtr rule) const {
        cpp_generator::ClassBuilder builder{std::string(rule->getName())};


        for (const auto& field : rule->m_fields) {
            auto type = getFieldType(*field);
            std::cout << "The type of the field " << *field << " is " << type << '\n';
        }

        return builder;
    }

  private:
    std::string getFieldType(const Rule::Field& field) const {
        TypeChecker typeChecker(m_grammar);
        auto res = typeChecker.check(*field.m_value);
        if (res) {
            return res->toString();
        }
        return "ERROR";
    }

    std::string typeCheckRuleElement(const Rule::Element& elt) const {

        if (elt.isSymbolRef()) {
            const auto& symRef = static_cast<const Rule::SymbolRef&>(elt);
            auto maybeSym = m_grammar.lookupSymbol(std::string(symRef.m_name));
            if (!maybeSym) {
                assert(false);
            }
            if (auto ptr = std::dynamic_pointer_cast<Rule>(*maybeSym)) {
                return std::string(ptr->getName());
            } else {
                return "Token";
            }
        } else if (elt.isChoice()) {
            const auto& choice = static_cast<const Rule::Choice&>(elt);
            std::set<std::string> types;
            for (const auto& c : choice.elements()) {
                types.emplace(typeCheckRuleElement(*c));
            }
            if (types.size() > 1) {
                assert(false);
            }
            return *types.begin();
        } else if (elt.isSequence()) {
            assert(false);
        }

        assert(false);
    }

    const Grammar& m_grammar;

  private:
};

RuleCXXGenerator::RuleCXXGenerator(const Grammar& grammar)
    : m_impl(std::make_unique<Impl>(grammar)) {}

RuleCXXGenerator::~RuleCXXGenerator() = default;


cpp_generator::ClassBuilder RuleCXXGenerator::generateClassFromRule(const RulePtr rule) const {
    return m_impl->generateClassFromRule(rule);
}

} // namespace grammar::generator
