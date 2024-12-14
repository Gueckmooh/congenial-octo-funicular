#pragma once

#include "tree_sitter/api.h"


namespace grammar::ts::detail {

struct TSDeleter {
    void operator()(TSParser* ptr) {
        ts_parser_delete(ptr);
    }
    void operator()(TSTree* ptr) {
        ts_tree_delete(ptr);
    }
};

} // namespace grammar::ts::detail
