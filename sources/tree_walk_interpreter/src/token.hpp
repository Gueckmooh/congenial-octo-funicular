#pragma once

#include <any>
#include <ostream>

#include "crafting_interpreters/utilities/printable.hpp"
#include "source_location.hpp"
#include "token_type.hpp"

namespace tlox {

class Token : public details::Printable<Token> {
  public:
    [[nodiscard]] inline Token(TokenType type,
                               std::string lexeme,
                               std::any literal,
                               SourceLocation loc)
        : m_type(type)
        , m_lexeme(std::move(lexeme))
        , m_literal(std::move(literal))
        , m_loc(std::move(loc)) {}

    inline TokenType type() const noexcept {
        return m_type;
    }

    inline std::string_view lexeme() const noexcept {
        return m_lexeme;
    }

    inline const std::any& literal() const noexcept {
        return m_literal;
    }

    inline const SourceLocation& loc() const noexcept {
        return m_loc;
    }

    inline void print(std::ostream& os) const {
        os << m_type << ' ' << '\'' << m_lexeme << '\'';
    }

  private:
    const TokenType m_type;
    const std::string m_lexeme;
    const std::any m_literal;
    const SourceLocation m_loc;
};

} // namespace tlox
