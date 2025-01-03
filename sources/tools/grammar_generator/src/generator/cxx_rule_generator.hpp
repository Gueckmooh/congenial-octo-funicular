#pragma once

#include <memory>

#include "grammar/grammar.hpp"

import cpp_generator;

namespace grammar::generator {

class RuleCXXGenerator {
  public:
    RuleCXXGenerator(const Grammar& grammar);

    ~RuleCXXGenerator();

    cpp_generator::ClassBuilder generateClassFromRule(const RulePtr rule) const;

  private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

} // namespace grammar::generator
