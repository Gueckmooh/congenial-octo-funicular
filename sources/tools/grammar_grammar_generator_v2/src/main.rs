mod args;
mod check;
mod error;
mod gen;
mod types;

mod node_types;

use args::Args;
use check::{TypeLookupPass, TypeTransform};
use clap::Parser;
use error::Error;
use gen::CPPClass;
use std::{
    borrow::Borrow,
    fs,
    io::{self},
    path::Path,
    rc::Rc,
};
use types::TypeRegistry;

fn parse_json_input(file_path: &Path) -> Result<Rc<TypeRegistry>, Error> {
    let content = match fs::read_to_string(file_path) {
        Ok(value) => value,
        Err(err) => {
            return Err(Error::BadInput {
                file: String::from(file_path.to_str().unwrap_or_default()),
                why: err.to_string(),
            })
        }
    };

    let parsed = match json::parse(&content) {
        Ok(value) => value,
        Err(err) => {
            return Err(Error::BadInput {
                file: String::from(file_path.to_str().unwrap_or_default()),
                why: err.to_string(),
            })
        }
    };

    match TypeRegistry::maybe_from_json(&parsed) {
        Some(res) => Ok(res),
        _ => {
            return Err(Error::BadInput {
                file: String::from(file_path.to_str().unwrap_or_default()),
                why: String::from("Could not parse types"),
            })
        }
    }
}

fn main() -> Result<(), Error> {
    let args = Args::parse();

    let file_path = Path::new(&args.file);
    if !file_path.exists() {
        return Err(Error::BadInput {
            file: args.file,
            why: String::from("file does not exist"),
        });
    }

    let registry = match parse_json_input(file_path) {
        Ok(reg) => reg,
        Err(err) => return Err(err),
    };

    // for ty in registry.types.iter() {
    //     println!("{:?}", ty);
    //     if ty.named {
    //         let c = CPPClass::from(ty.borrow());
    //         println!("{:?}", c);
    //         c.gen(&mut io::stdout()).unwrap();
    //     }
    // }

    println!("DONG TRANSFORMATIONS");
    let mut transform = TypeTransform::new();
    transform.add_pass(TypeLookupPass::new());
    let registry = transform.apply_passes(registry);

    for ty in registry.unwrap().types.iter() {
        // println!("{:?}", ty);
        if ty.named {
            let c = CPPClass::from(ty.borrow());
            // println!("{:?}", c);
            c.gen(&mut io::stdout()).unwrap();
        }
    }

    return Ok(());
}
