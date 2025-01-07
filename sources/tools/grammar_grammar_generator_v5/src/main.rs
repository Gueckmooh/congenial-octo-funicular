mod args;

use anyhow::{ensure, Result};
use args::Args;
use clap::Parser;
use grammar_grammar_generator_v5::{
    cpp::{Class, Field, Type, Visibility},
    generator::{Generate, Generator},
    node_types::{self, NodeInfoJSON},
};

fn main() -> Result<()> {
    let args = Args::parse();
    let node_types = node_types::deserialize_from_file(&args.file)?;
    ensure!(!node_types.is_empty(), "There is not enough node types");
    println!("{:#?}", node_types[0]);

    let classes: Vec<Class> = node_types
        .iter()
        .filter_map(NodeInfoJSON::as_class)
        .collect();
    ensure!(!classes.is_empty(), "I'm not happy");
    println!("{}", Generator::generate_str(&classes[0])?);

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
