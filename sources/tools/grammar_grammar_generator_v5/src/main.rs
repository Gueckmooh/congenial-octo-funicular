use anyhow::Result;
use grammar_grammar_generator_v5::{
    cpp::{Class, Field, Type, Visibility},
    generator::{Generate, Generator},
};

fn main() -> Result<()> {
    let mut gen: Generator<String> = Generator::default();
    let s = Class::new(
        "Foo",
        vec![
            Field::new("baz", Type::String, Visibility::Private),
            Field::new("bocc", Type::String, Visibility::Private),
            Field::new("bar", Type::String, Visibility::Public),
        ],
    );
    gen.generate(&s)?;
    print!("{gen}");
    Ok(())
}
