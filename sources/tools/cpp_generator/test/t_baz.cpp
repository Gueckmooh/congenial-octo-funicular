#include <catch2/catch_test_macros.hpp>

import LibraryCXX20Module;

TEST_CASE("Testing baz function", "[baz]") {
    REQUIRE(crafting_interpreters::library_cxx20_module::baz() == "Hello, World!");
}
