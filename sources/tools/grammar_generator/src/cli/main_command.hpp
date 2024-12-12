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


} // namespace grammar::cli
