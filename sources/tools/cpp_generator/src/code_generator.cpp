module;

#include <ostream>
#include <format>

#include "crafting_interpreters/cpp_generator/export.hpp"

export module cpp_generator:CodeGenerator;


namespace cpp_generator {

export class CodeGenerator;

namespace detail {

export class CPP_GENERATOR_EXPORT Generatable {
  public:
    virtual ~Generatable() = default;
    virtual void generate(CodeGenerator& generator) const = 0;
};

} // namespace detail

export class CPP_GENERATOR_EXPORT CodeGenerator {
  public:
    CodeGenerator(std::ostream& os)
        : m_os(os) {}

    CodeGenerator& indent() {
        m_os << indentation();
        return *this;
    }

    CodeGenerator& halfIndent() {
        m_os << halfIndentation();
        return *this;
    }

    CodeGenerator& write(std::string_view content) {
        m_os << content;
        return *this;
    }

    template <class... Args>
    CodeGenerator& write(std::format_string<Args...> fmt, Args&&... args) {
        m_os << std::format(fmt, std::forward<Args>(args)...);
        return *this;
    }

    CodeGenerator& newline() {
        m_os << '\n';
        return *this;
    }

    void updateIndentation(int value) {
        if (value < 0) {
            if (m_indentation < static_cast<std::size_t>(-value)) {
                m_indentation = 0;
                return;
            }
            m_indentation -= static_cast<std::size_t>(-value);
            return;
        }
        m_indentation += static_cast<std::size_t>(value);
    }

  private:
    std::string indentation() const {
        return std::string(m_indentation * 4, ' ');
    }

    std::string halfIndentation() const {
        if (m_indentation == 0) {
            return "  ";
        }
        return std::string((m_indentation - 1) * 4, ' ') + "  ";
    }

  private:
    std::ostream& m_os;
    std::size_t m_indentation = 0;
};
} // namespace cpp_generator
