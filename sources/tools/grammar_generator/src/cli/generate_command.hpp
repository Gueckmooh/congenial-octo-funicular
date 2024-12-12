#pragma once

#include <filesystem>

#include "command.hpp"

namespace grammar::cli {

class GenerateCommand final : public SubCommand {
  public:
    void init(CLI::App& app) override;
    int run() override;

  private:
    std::filesystem::path m_grammarFile;
};

} // namespace grammar::cli
