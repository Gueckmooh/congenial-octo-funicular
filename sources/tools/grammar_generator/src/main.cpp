#include <cstdlib>
#include <memory>

#include "CLI/CLI.hpp"


#include "cli/main_command.hpp"
#include "cli/generate_command.hpp"


int main(int argc, char** argv) {
    auto mainCmd = grammar::cli::makeMainCommand<grammar::cli::GenerateCommand>();
    mainCmd->init();

    CLI11_PARSE(mainCmd->app(), argc, argv);

    return mainCmd->run();
}
