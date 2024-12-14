module;

#include <ostream>
#include <sstream>
#include <string>

#include "crafting_interpreters/cpp_generator/export.hpp"

export module cpp_generator:Printable;

namespace cpp_generator::detail {

export class CPP_GENERATOR_EXPORT Printable {
  public:
    virtual ~Printable() = default;
    virtual void print(std::ostream& os) const = 0;

    std::string toString() const {
        std::stringstream ss;
        this->print(ss);
        return ss.str();
    }

    CPP_GENERATOR_EXPORT friend std::ostream& operator<<(std::ostream& os, const Printable& v) {
        v.print(os);
        return os;
    }
};

} // namespace cpp_generator::detail
