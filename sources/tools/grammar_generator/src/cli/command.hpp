#pragma once

#include "CLI/CLI.hpp"

namespace grammar::cli {

class Command {
  public:
    Command(CLI::App& mainApp)
        : m_mainApp(mainApp) {}

    virtual ~Command() = default;

    virtual void init() = 0;
    virtual int run() = 0;
    virtual bool shouldRun() {
        if (m_app) {
            return m_app->parsed();
        }
        return false;
    }

  protected:
    CLI::App* m_app;
    CLI::App& m_mainApp;
};

} // namespace grammar::cli
