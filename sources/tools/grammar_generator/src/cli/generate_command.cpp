#include <filesystem>
#include <iostream>

#include "generate_command.hpp"

#include "ts/parser.hpp"
#include "ts/node.hpp"
#include "ts/tree.hpp"

#include "grammar/grammar.hpp"
#include "grammar/grammar_compiler.hpp"

#include "generator/cxx_rule_generator.hpp"

import cpp_generator;

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

void GenerateCommand::init(CLI::App& app) {
    m_app = app.add_subcommand("generate", "Generate grammar");
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

    grammar::generator::RuleCXXGenerator generator(grammar);
    auto c = generator.generateClassFromRule(grammar.getRules().front());

    cpp_generator::CodeGenerator gen(std::cout);
    c.generate(gen);

    return 0;
}

} // namespace grammar::cli
