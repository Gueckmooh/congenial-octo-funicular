#include "command.hpp"

namespace grammar::cli {

void Command::registerSubCommand(std::unique_ptr<SubCommand> subCommand) {
    m_subCommands.emplace_back(std::move(subCommand));
}

CLI::App& Command::app() {
    if (!m_app) {
        init();
    }
    return *m_app;
}

void Command::initSubCommands(CLI::App& app) {
    for (auto& subCommand : m_subCommands) {
        subCommand->init(app);
    }
}

bool SubCommand::shouldRun() const {
    if (m_app) {
        return m_app->parsed();
    }
    return false;
}

} // namespace grammar::cli
