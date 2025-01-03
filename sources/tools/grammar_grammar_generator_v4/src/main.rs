use std::fmt::Write;

use anyhow::Result;
use grammar_grammar_generator_v4::{
    cpp::{Class, Field, Type},
    cpp_generator::{CPPGenerator, Generate},
};

fn main() -> Result<()> {
    let class = Class::new(
        "Foo",
        vec![
            Field::new(Type::String, "bar"),
            Field::new(Type::String, "baz"),
        ],
    );
    let mut gen = CPPGenerator::default();
    gen.generate(&class)?;
    println!("{gen}");
    println!("{class:#?}");
    Ok(())
}
