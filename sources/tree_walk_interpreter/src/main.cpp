#include <iostream>
#include <filesystem>

void runFile(const std::filesystem::path& scriptPath) {
    (void)scriptPath;
}

void runPrompt() {}

namespace {

class ExitCode {
  public:
    static const int SUCCESS = 0;
    static const int USAGE = 64;
};

} // namespace

int main(int argc, char** argv) {
    if (argc > 2) {
        std::cerr << "Usage tlox [script]" << std::endl;
        return ExitCode::USAGE;
    }

    if (argc == 2) {
        runFile(argv[1]);
    } else {
        runPrompt();
    }

    return ExitCode::SUCCESS;
}
