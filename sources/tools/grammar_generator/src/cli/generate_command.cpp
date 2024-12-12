#include <filesystem>
#include <iostream>

#include "generate_command.hpp"

#include "../parser.hpp"
#include "../node.hpp"
#include "../tree.hpp"
#include "../grammar.hpp"
#include "../grammar_compiler.hpp"

namespace grammar::cli {

namespace {

using Source = std::shared_ptr<std::string>;

Source readAllFile(const std::filesystem::path& path) {
    if (!std::filesystem::exists(path)) {
        return {};
    }

    std::ifstream ifs{path};
    std::ostringstream oss;
    oss << ifs.rdbuf();
    auto source = std::make_shared<std::string>(oss.str());
    return source;
}

} // namespace

void GenerateCommand::init() {
    m_app = m_mainApp.add_subcommand("generate", "Generate grammar");
    m_app->add_option("--input-grammar,-i", m_grammarFile, "The grammar file to parse");
}

int GenerateCommand::run() {
    grammar::ts::Parser parser;

    auto source = readAllFile(m_grammarFile);
    if (!source) {
        std::cerr << "Error occured while reading input grammar file " << m_grammarFile
                  << std::endl;
        return 1;
    }

    auto tree = parser.parse(*source);

    grammar::GrammarCompiler compiler{tree};
    auto grammar = compiler.compile();

    std::cout << grammar << std::endl;

    return 0;
}

} // namespace grammar::cli
