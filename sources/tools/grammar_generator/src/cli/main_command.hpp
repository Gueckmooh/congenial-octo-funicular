#pragma once

#include <memory>
#include <concepts>

#include "command.hpp"

namespace grammar::cli {

class MainCommand final : public Command {
  public:
    void init() override;
    int run() override;
};

template <std::derived_from<SubCommand>... SubCommandsT>
inline constexpr std::unique_ptr<MainCommand> makeMainCommand() {
    auto command = std::make_unique<MainCommand>();
    (
        [&]() {
            auto subCommand = std::make_unique<SubCommandsT>();
            command->registerSubCommand(std::move(subCommand));
        }(),
        ...);
    return command;
}

} // namespace grammar::cli
