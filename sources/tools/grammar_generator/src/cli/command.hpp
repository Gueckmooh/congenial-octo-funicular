#pragma once

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

} // namespace grammar::cli
