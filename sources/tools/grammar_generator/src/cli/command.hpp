#pragma once

#include <concepts>
#include "CLI/CLI.hpp"

namespace grammar::cli {

class ICommand {
  public:
    virtual ~ICommand() = default;

    virtual int run() = 0;
};

class SubCommand;

class Command : public ICommand {
  public:
    virtual void init() = 0;
    void registerSubCommand(std::unique_ptr<SubCommand> subCommand);
    CLI::App& app();

  protected:
    void initSubCommands(CLI::App& app);

  protected:
    std::unique_ptr<CLI::App> m_app;
    std::vector<std::unique_ptr<SubCommand>> m_subCommands;
};

class SubCommand : public ICommand {
  public:
    virtual void init(CLI::App& app) = 0;
    bool shouldRun() const;

  protected:
    CLI::App* m_app;
};

template <std::derived_from<Command> CommandT, std::derived_from<SubCommand>... SubCommandsT>
inline constexpr std::unique_ptr<CommandT> makeCommand() {
    auto command = std::make_unique<CommandT>();
    (
        [&] constexpr {
            auto subCommand = std::make_unique<SubCommandsT>();
            command->registerSubCommand(std::move(subCommand));
        }(),
        ...);
    return command;
}

} // namespace grammar::cli
