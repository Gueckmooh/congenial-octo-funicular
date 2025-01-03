use std::fs;

use gen::gen_class_from_type;

mod gen;
mod ty;

fn main() {
    let content = fs::read_to_string(
        "/home/ebrignon/dev/crafring_interpreters/sources/tools/tree-sitter-grammar/src/node-types.json",
    )
    .unwrap();
    let parsed = json::parse(&content).unwrap();
    assert!(parsed.is_array());

    let v = ty::TypeRegistry::from_json(&parsed).unwrap();

    for ty in v.types.iter() {
        println!("{:?}", &ty);
    }

    for ty in v.types.iter() {
        gen_class_from_type(&ty);
    }
}
