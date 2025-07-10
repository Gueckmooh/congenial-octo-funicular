mod cpp;
mod template_functions;

use anyhow::{ensure, Result};
use convert_case::{Case, Casing};
use serde::Serialize;
use std::{fs::File, io::Write, path::Path};
use template_functions::register_functions;
use tera::{Context, Tera};

#[derive(Serialize)]
struct ClassGenContext {
    class: cpp::Class,
    hpp_file_name: String,
    cpp_file_name: String,
}

fn new_tera() -> Result<Tera> {
    let templates_glob = format!("{}/templates/**/*", env!("CARGO_MANIFEST_DIR"));
    let mut tera = Tera::new(&templates_glob).map_err(anyhow::Error::from)?;
    register_functions(&mut tera);
    Ok(tera)
}

fn get_class_gen_context(class: &model::Class) -> ClassGenContext {
    let file_base_name = class.name().to_case(Case::Snake);
    let hpp_file_name = format!("{file_base_name}.hpp");
    let cpp_file_name = format!("{file_base_name}.cpp");
    let class = cpp::Class {
        name: class.name().into(),
        methods: vec![],
        fields: class
            .fields()
            .iter()
            .map(|v| v.as_ref().clone().into())
            .collect(),
        attributes: cpp::ClassAttributes {
            has_default: true,
            is_copyable: true,
            is_printable: true,
            is_ref_counted: class.attributes().is_ref_counted,
            may_be_null: class.attributes().may_be_null,
        },
    };
    ClassGenContext {
        class,
        hpp_file_name,
        cpp_file_name,
    }
}

pub fn generate_class_in_directory(class: &model::Class, directory: &Path) -> Result<()> {
    let tera = new_tera()?;
    let is_ref_counted = class.attributes().is_ref_counted;
    let class_gen_context = get_class_gen_context(class);
    let context = Context::from_serialize(&class_gen_context)?;
    println!("{context:#?}");

    let hpp_file_path = directory.join(class_gen_context.hpp_file_name);
    let cpp_file_path = directory.join(class_gen_context.cpp_file_name);

    if is_ref_counted {
        {
            let mut file = File::create(hpp_file_path)?;
            write!(file, "{}", tera.render("ref_counted/class.hpp", &context)?)?;
            file.sync_all()?;
        }
        {
            let mut file = File::create(cpp_file_path)?;
            write!(file, "{}", tera.render("ref_counted/class.cpp", &context)?)?;
            file.sync_all()?;
        }
    }

    Ok(())
}

pub fn generate_package_in_directory(package: &model::Package, directory: &Path) -> Result<()> {
    ensure!(
        directory.is_dir() || !directory.exists(),
        "The path exists and it is not a directory"
    );
    if !directory.exists() {
        std::fs::create_dir_all(directory)?;
    }

    for declaration in package.declarations() {
        match declaration {
            model::package::Declaration::Class(rc) => {
                generate_class_in_directory(rc.as_ref(), directory)?;
            }
        }
    }

    Ok(())
}
