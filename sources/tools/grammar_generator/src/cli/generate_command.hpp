#pragma once

#include <filesystem>

#include "command.hpp"

namespace grammar::cli {

class GenerateCommand final : public Command {
  public:
    using Command::Command;

    void init() override;
    int run() override;

  private:
    std::filesystem::path m_grammarFile;
};

} // namespace grammar::cli
