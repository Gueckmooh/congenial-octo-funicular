#include <catch2/catch_test_macros.hpp>

#include "crafting_interpreters/library_module/foo.hpp"

TEST_CASE("Testing foo function", "[foo]") {
    REQUIRE(crafting_interpreters::library_module::foo() == "Hello, World!");
}
