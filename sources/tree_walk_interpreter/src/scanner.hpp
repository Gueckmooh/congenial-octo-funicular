#pragma once

#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>

#include "source_location.hpp"
#include "token.hpp"
#include "token_type.hpp"

namespace tlox {

class DiagnosticReporter {
  public:
    DiagnosticReporter() = default;

    void report(const std::string& message,
                const std::string& where,
                const tlox::SourceLocation& loc) {
        std::cerr << loc << " Error " << where << ": " << message << std::endl;
        m_hadError = true;
    }

    void error(const std::string& message, const tlox::SourceLocation& loc) {
        report(message, "", loc);
    }

    inline bool hadError() const {
        return m_hadError;
    }

  private:
    bool m_hadError = false;
};

class Scanner {
  public:
    Scanner(std::string source, DiagnosticReporter& diagnosticReporter)
        : m_source(std::move(source))
        , m_start(m_source.begin())
        , m_current(m_start)
        , m_diagnosticReporter(diagnosticReporter) {}

    const std::vector<Token>& scanTokens() {
        while (!isAtEnd()) {
            m_start = m_current;
            scanToken();
        }

        m_tokens.emplace_back(TokenType::END_OF_FILE, std::string{}, std::any{}, m_loc);

        return m_tokens;
    }

  private:
    bool isAtEnd() const {
        return m_current >= m_source.end();
    }

    char advance() {
        auto c = *m_current++;
        if (c == '\n') {
            m_loc.advanceLine();
        } else {
            m_loc.advanceColumn();
        }
        return c;
    }

    void scanToken() {
        std::any foo;
        auto c = advance();
        switch (c) {
        case '(':
            addToken(TokenType::LEFT_PAREN);
            break;
        case ')':
            addToken(TokenType::RIGHT_PAREN);
            break;
        case '{':
            addToken(TokenType::LEFT_BRACE);
            break;
        case '}':
            addToken(TokenType::RIGHT_BRACE);
            break;
        case ',':
            addToken(TokenType::COMMA);
            break;
        case '.':
            addToken(TokenType::DOT);
            break;
        case '-':
            addToken(TokenType::MINUS);
            break;
        case '+':
            addToken(TokenType::PLUS);
            break;
        case ';':
            addToken(TokenType::SEMICOLON);
            break;
        case '*':
            addToken(TokenType::STAR);
            break;
        case '!':
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;
        case '/':
            if (match('/')) {
                // A comment goes until the end of the line.
                while (peek() != '\n' && !isAtEnd()) {
                    advance();
                }
            } else {
                addToken(TokenType::SLASH);
            }
            break;
        case ' ':
        case '\r':
        case '\t':
        case '\n':
            // Ignore whitespace.
            break;
        case '"':
            string();
            break;
        default:
            if (isDigit(c)) {
                number();
            } else if (isAlpha(c)) {
                identifier();
            } else {
                m_diagnosticReporter.error("Unexpected character.", m_loc);
            }
            break;
        }
    }

    bool match(char expected) {
        if (isAtEnd()) {
            return false;
        }
        if (*m_current != expected) {
            return false;
        }

        (void)advance();
        return true;
    }

    char peek() {
        if (isAtEnd()) {
            return '\0';
        }
        return *m_current;
    }

    char peekNext() {
        if (m_current + 1 >= m_source.end())
            return '\0';
        return *(m_current + 1);
    }

    void addToken(TokenType type) {
        addToken(type, {});
    }

    void addToken(TokenType type, std::any literal) {
        std::string text{m_start, m_current};
        m_tokens.emplace_back(type, text, literal, m_loc);
    }

    void string() {
        while (peek() != '"' && !isAtEnd()) {
            advance();
        }

        if (isAtEnd()) {
            m_diagnosticReporter.error("Unterminated string.", m_loc);
            return;
        }

        // The closing ".
        advance();

        // Trim the surrounding quotes.
        std::string value{m_start + 1, m_current - 1};
        addToken(TokenType::STRING, value);
    }
    void identifier() {
        while (isAlphaNumeric(peek()))
            advance();

        std::string text{m_start, m_current};
        if (auto it = m_keyworks.find(text); it != m_keyworks.end()) {
            addToken(it->second);
        } else {
            addToken(TokenType::IDENTIFIER);
        }
    }

    bool isAlpha(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
    }

    bool isAlphaNumeric(char c) {
        return isAlpha(c) || isDigit(c);
    }

    bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    void number() {
        while (isDigit(peek()))
            advance();

        // Look for a fractional part.
        if (peek() == '.' && isDigit(peekNext())) {
            // Consume the "."
            advance();

            while (isDigit(peek()))
                advance();
        }

        try {
            auto val = std::stod(std::string{m_start, m_current});
            addToken(TokenType::NUMBER, val);
        } catch (const std::invalid_argument& e) {
            m_diagnosticReporter.error(e.what(), m_loc);
        } catch (const std::out_of_range& e) {
            m_diagnosticReporter.error(e.what(), m_loc);
        } catch (...) {
            m_diagnosticReporter.error("unknown error", m_loc);
        }
    }

  private:
    const std::string m_source;
    std::string::const_iterator m_start;
    std::string::const_iterator m_current;
    SourceLocation m_loc;
    std::vector<Token> m_tokens;
    DiagnosticReporter& m_diagnosticReporter;

  private:
    static const std::map<std::string, TokenType> m_keyworks;
};

} // namespace tlox
