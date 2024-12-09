#include <iostream>
#include <filesystem>
#include <ostream>
#include "printable.hpp"
#include "source_location.hpp"

#include "token.hpp"

namespace {

class ExitCode {
  public:
    enum : int {
        SUCCESS = 0,
        USAGE = 64,
        FAILURE = 65,
    };
};

class Lox {
  public:
    void runFile(const std::filesystem::path& scriptPath) {
        (void)scriptPath;
    }

    void runPrompt() {}

    void report(const std::string& message,
                const std::string& where,
                const tlox::SourceLocation& loc) {
        std::cerr << loc << " Error " << where << ": " << message << std::endl;
        m_hadError = true;
    }

    void error(const std::string& message, const tlox::SourceLocation& loc) {
        report(message, "", loc);
    }

    bool hadError() const {
        return m_hadError;
    }

  private:
    bool m_hadError = false;
};

} // namespace

int main(int argc, char** argv) {
    if (argc > 2) {
        std::cerr << "Usage tlox [script]" << std::endl;
        return ExitCode::USAGE;
    }

    Lox lox;
    if (argc == 2) {
        lox.runFile(argv[1]);
    } else {
        lox.runPrompt();
    }

    if (lox.hadError()) {
        return ExitCode::FAILURE;
    }

    std::string foo = "foo bar baz";
    std::string bar{foo.begin() + 4, foo.begin() + 7};
    std::cout << bar << std::endl;

    return ExitCode::SUCCESS;
}
