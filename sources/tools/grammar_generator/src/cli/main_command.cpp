#include "main_command.hpp"

namespace grammar::cli {

MainCommand::MainCommand()
    : m_app("Grammar generator") {}

void MainCommand::init() {
    for (auto& subCommand : m_subCommands) {
        subCommand->init();
    }
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

void MainCommand::registerSubCommand(std::unique_ptr<Command> subCommand) {
    m_subCommands.emplace_back(std::move(subCommand));
}

CLI::App& MainCommand::app() {
    return m_app;
}


} // namespace grammar::cli
