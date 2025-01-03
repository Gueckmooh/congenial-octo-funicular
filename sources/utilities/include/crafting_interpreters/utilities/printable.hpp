#pragma once

#include <concepts>
#include <ostream>
#include <sstream>
#include <string>

namespace tlox::details {

template <typename T>
concept IsPrintable = requires(T a, std::ostream& os) {
    {
        a.print(os)
    } -> std::same_as<void>;
};

template <typename Derived>
class Printable {
  public:
    friend inline std::ostream& operator<<(std::ostream& os, const Derived& printable) {
        printable.print(os);
        return os;
    }

    inline std::string toString(this const Derived& self) noexcept {
        std::stringstream ss;
        self.print(ss);
        return ss.str();
    }
};


} // namespace tlox::details
