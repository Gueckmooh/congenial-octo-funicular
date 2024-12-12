#pragma once

#include <vector>
#include <memory>

#include "CLI/CLI.hpp"

#include "command.hpp"

namespace grammar::cli {

class MainCommand {
  public:
    MainCommand();

    void init();
    int run();

    void registerSubCommand(std::unique_ptr<Command> subCommand);
    CLI::App& app();

  private:
    CLI::App m_app;
    std::vector<std::unique_ptr<Command>> m_subCommands;
};

template <typename... SubCommandsT>
inline constexpr std::unique_ptr<MainCommand> makeMainCommand() {
    auto command = std::make_unique<MainCommand>();
    (
        [&]() {
            auto subCommand = std::make_unique<SubCommandsT>(command->app());
            command->registerSubCommand(std::move(subCommand));
        }(),
        ...);
    return command;
}

} // namespace grammar::cli
