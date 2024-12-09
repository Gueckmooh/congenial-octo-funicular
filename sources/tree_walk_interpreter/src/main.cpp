#include <fstream>
#include <iostream>
#include <filesystem>
#include <ostream>
#include <sstream>
#include <string>
#include "printable.hpp"
#include "scanner.hpp"
#include "source_location.hpp"

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
    Lox(tlox::DiagnosticReporter& diag)
        : m_diagnosticReporter(diag) {}

    void runFile(const std::filesystem::path& scriptPath) {
        if (!std::filesystem::exists(scriptPath)) {
            m_diagnosticReporter.error("File does not exist", {});
            return;
        }
        // Reading the entire file
        std::ifstream ifs{scriptPath};
        std::ostringstream oss;
        oss << ifs.rdbuf();
        std::string content = oss.str();

        run(content);
    }

    void runPrompt() {
        for (;;) {
            std::string line;
            std::cout << "> ";
            std::getline(std::cin, line);
            if (line.empty()) {
                break;
            }
            run(line);
        }
    }

  private:
    void run(const std::string& source) {
        tlox::Scanner scanner{source, m_diagnosticReporter};
        auto tokens = scanner.scanTokens();

        if (m_diagnosticReporter.hadError()) {
            return;
        }

        for (const auto& token : tokens) {
            std::cout << token << std::endl;
        }
    }

  private:
    tlox::DiagnosticReporter& m_diagnosticReporter;
};

} // namespace

int main(int argc, char** argv) {
    if (argc > 2) {
        std::cerr << "Usage tlox [script]" << std::endl;
        return ExitCode::USAGE;
    }

    tlox::DiagnosticReporter diag;
    Lox lox{diag};
    if (argc == 2) {
        lox.runFile(argv[1]);
    } else {
        lox.runPrompt();
    }

    if (diag.hadError()) {
        return ExitCode::FAILURE;
    }

    return ExitCode::SUCCESS;
}
