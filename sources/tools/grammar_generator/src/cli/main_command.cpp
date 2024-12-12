#include "main_command.hpp"

namespace grammar::cli {


void MainCommand::init() {
    m_app = std::make_unique<CLI::App>("Grammar generator");
    initSubCommands(*m_app);
}

int MainCommand::run() {
    for (auto& subCommand : m_subCommands) {
        if (subCommand->shouldRun()) {
            return subCommand->run();
        }
    }
    std::cout << "No command run" << std::endl;
    return 1;
}

} // namespace grammar::cli
