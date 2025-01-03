#include "type_checker.hpp"
#include <algorithm>
#include <functional>
#include <memory>
#include "grammar/grammar.hpp"

namespace grammar::generator {

class TypeChecker::Impl {
  public:
    Impl(const Grammar& grammar)
        : m_grammar(grammar) {}

    std::shared_ptr<TypeChecker::IType> check(const Rule::Element& element) const {
        if (element.isChoice()) {
            return check(static_cast<const Rule::Choice&>(element));
        } else if (element.isSequence()) {
            return check(static_cast<const Rule::Sequence&>(element));
        } else if (element.isSymbolRef()) {
            return check(static_cast<const Rule::SymbolRef&>(element));
        } else {
            return {};
        }
    }


    std::shared_ptr<TypeChecker::IType> check(const Rule::Choice& element) const {
        std::vector<std::shared_ptr<IType>> orTypes;
        for (const auto& elt : element.elements()) {
            auto ty = check(*elt);
            if (!ty) {
                ty = std::make_shared<Type>(std::string{"ERROR"});
            }
            if (orTypes.empty()) {
                orTypes.emplace_back(ty);
            }
            if (std::find_if(orTypes.begin(), orTypes.end(),
                             [&ty](const auto& e) { return *e == *ty; }) != orTypes.end()) {
                orTypes.emplace_back(ty);
            }
        }
        auto orTy = std::make_shared<Or>();
        orTy->types = std::move(orTypes);
        return orTy;
    }


    std::shared_ptr<TypeChecker::IType> check(const Rule::Sequence& element) const {
        if (element.elements().size() == 1) {
            return check(*element.elements().front());
        }
        return nullptr;
    }


    std::shared_ptr<TypeChecker::IType> check(const Rule::SymbolRef& element) const {
        auto maybeSymbol = m_grammar.lookupSymbol(element.m_name);
        if (!maybeSymbol) {
            return nullptr;
        }
        auto symbol = *maybeSymbol;

        if (symbol->isTerminal()) {
            std::make_shared<Type>("Token");
        } else if (symbol->isRule()) {
            auto rule = std::static_pointer_cast<Rule>(symbol);
            std::make_shared<Type>(std::string(rule->getName()));
        }

        return nullptr;
    }


  private:
    const Grammar& m_grammar;
};

TypeChecker::TypeChecker(const Grammar& grammar)
    : m_impl(std::make_unique<Impl>(grammar)) {}
TypeChecker::~TypeChecker() = default;

std::shared_ptr<TypeChecker::IType> TypeChecker::check(const Rule::Element& element) const {
    return m_impl->check(element);
}


} // namespace grammar::generator
