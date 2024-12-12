#include <cstdlib>
#include <memory>

#include "CLI/CLI.hpp"


#include "cli/main_command.hpp"
#include "cli/generate_command.hpp"


int main(int argc, char** argv) {
    using namespace grammar;
    auto mainCmd = cli::makeCommand<cli::MainCommand, cli::GenerateCommand>();
    mainCmd->init();

    CLI11_PARSE(mainCmd->app(), argc, argv);

    return mainCmd->run();
}
