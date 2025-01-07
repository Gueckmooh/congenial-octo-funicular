mod cpp;
mod template_functions;

use anyhow::{ensure, Result};
use convert_case::{Case, Casing};
use serde::Serialize;
use std::{collections::HashSet, fs::File, io::Write, path::Path};
use template_functions::register_functions;
use tera::{Context, Tera};

#[derive(Serialize)]
struct ClassGenContext {
    class: cpp::Class,
    hpp_file_name: String,
    cpp_file_name: String,

    dependencies: Vec<cpp::Type>,
}

fn new_tera() -> Result<Tera> {
    let templates_glob = format!("{}/templates/**/*", env!("CARGO_MANIFEST_DIR"));
    let mut tera = Tera::new(&templates_glob).map_err(anyhow::Error::from)?;
    register_functions(&mut tera);
    Ok(tera)
}

fn get_function_dependencies(function: &model::Function) -> Vec<cpp::Type> {
    get_type_dependencies(function.return_ty())
        .into_iter()
        .chain(
            function
                .params()
                .iter()
                .flat_map(|v| get_variable_dependencies(v)),
        )
        .collect()
}

fn get_variable_dependencies(variable: &model::Variable) -> Vec<cpp::Type> {
    get_type_dependencies(variable.ty())
}

fn get_type_dependencies(ty: &model::Type) -> Vec<cpp::Type> {
    match ty {
        model::Type::Void => vec![],
        model::Type::Int32 => vec![cpp::Type::Int32],
        model::Type::String => vec![cpp::Type::String],
        model::Type::Type(name) => vec![cpp::Type::Object(name.into())],
    }
}

fn get_class_dependencies(class: &model::Class) -> Vec<cpp::Type> {
    let set: Vec<cpp::Type> = class
        .methods()
        .iter()
        .flat_map(|f| get_function_dependencies(f.as_ref()))
        .collect();
    let set = set
        .into_iter()
        .chain(
            class
                .fields()
                .iter()
                .flat_map(|f| get_variable_dependencies(f.as_ref())),
        )
        .collect::<HashSet<cpp::Type>>()
        .into_iter()
        .collect();

    set
}

fn get_class_gen_context(class: &model::Class) -> ClassGenContext {
    let file_base_name = class.name().to_case(Case::Snake);
    let hpp_file_name = format!("{file_base_name}.hpp");
    let cpp_file_name = format!("{file_base_name}.cpp");
    let dependencies = get_class_dependencies(&class);
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
        },
    };
    ClassGenContext {
        class,
        hpp_file_name,
        cpp_file_name,
        dependencies,
    }
}

pub fn generate_class_in_directory(class: &model::Class, directory: &Path) -> Result<()> {
    let tera = new_tera()?;
    let class_gen_context = get_class_gen_context(class);
    let context = Context::from_serialize(&class_gen_context)?;
    println!("{context:#?}");

    let hpp_file_path = directory.join(class_gen_context.hpp_file_name);
    let cpp_file_path = directory.join(class_gen_context.cpp_file_name);

    {
        let mut hpp_file = File::create(hpp_file_path)?;
        write!(hpp_file, "{}", tera.render("class_decl.hpp", &context)?)?;
        hpp_file.sync_all()?;
    }

    {
        let mut cpp_file = File::create(cpp_file_path)?;
        write!(cpp_file, "{}", tera.render("class_def.cpp", &context)?)?;
        cpp_file.sync_all()?;
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
