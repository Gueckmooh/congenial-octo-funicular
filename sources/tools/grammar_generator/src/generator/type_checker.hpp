#pragma once

#include <memory>
#include <ostream>
#include <vector>

#include "crafting_interpreters/utilities/printable.hpp"
#include "grammar/grammar.hpp"

namespace grammar::generator {

class TypeChecker {
  public:
    struct IType : public tlox::details::Printable<IType> {
        virtual ~IType() = default;
        virtual bool operator==(const IType& other) const = 0;
        virtual bool isType() const {
            return false;
        }
        virtual bool isOr() const {
            return false;
        }
        virtual void print(std::ostream& os) const = 0;
    };
    struct Type : public IType {
        Type(std::string name)
            : name(std::move(name)) {}
        bool operator==(const IType& other) const override {
            if (other.isOr()) {
                return false;
            }
            return name == static_cast<const Type&>(other).name;
        }

        bool isType() const final {
            return true;
        }

        void print(std::ostream& os) const override {
            os << name;
        }
        std::string name;
    };
    struct Or : public IType {
        std::vector<std::shared_ptr<IType>> types;

        bool operator==(const IType& other) const override {
            if (other.isType()) {
                return false;
            }
            const auto& otherOr = static_cast<const Or&>(other);
            return types == otherOr.types;
        }

        bool isOr() const final {
            return true;
        }

        void print(std::ostream& os) const override {
            for (std::size_t idx = 0; idx < types.size(); idx += 1) {
                auto ty = types.at(idx);
                if (ty) {
                    os << *ty;
                } else {
                    os << "ERROR";
                }
                if (idx < types.size() - 1) {
                    os << " | ";
                }
            }
        }
    };

  public:
    TypeChecker(const Grammar& grammar);
    ~TypeChecker();

    std::shared_ptr<TypeChecker::IType> check(const Rule::Element& element) const;

  private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

} // namespace grammar::generator
