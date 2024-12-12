#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>

#include "parser.hpp"
#include "node.hpp"
#include "tree.hpp"
#include "grammar.hpp"
#include "grammar_compiler.hpp"

using Source = std::shared_ptr<std::string>;

Source readAllFile(const std::filesystem::path& path) {
    std::ifstream ifs{path};
    std::ostringstream oss;
    oss << ifs.rdbuf();
    auto source = std::make_shared<std::string>(oss.str());
    return source;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Need one parameter" << std::endl;
        return 1;
    }
    std::filesystem::path path{argv[1]};

    grammar::ts::Parser parser;

    auto source = readAllFile(path);
    auto tree = parser.parse(*source);

    grammar::GrammarCompiler compiler{tree};
    auto grammar = compiler.compile();

    std::cout << grammar << std::endl;

    return 0;
}
