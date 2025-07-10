use anyhow::Result;
use model::{package::Declaration, Class, Package, Type, Variable};
use std::{path::Path, rc::Rc};

fn get_package() -> Package {
    let point_class = Rc::new(Class::new(
        "Point",
        vec![],
        vec![
            Variable::new("x", Type::Int32).as_mutable(),
            Variable::new("y", Type::Int32).as_mutable(),
        ],
        model::class::Attributes {
            is_ref_counted: true,
            may_be_null: false,
        },
    ));

    let circle_class = Rc::new(Class::new(
        "Circle",
        vec![],
        vec![
            Variable::new("center", Type::Type("Point".into())).as_mutable(),
            Variable::new("radius", Type::Int32).as_mutable(),
        ],
        model::class::Attributes {
            is_ref_counted: true,
            may_be_null: true,
        },
    ));

    Package::new(
        "geometry",
        vec![
            Declaration::Class(point_class),
            Declaration::Class(circle_class),
        ],
    )
}

fn main() -> Result<()> {
    let package = get_package();
    println!("{package:#?}");

    cpp_generator::generate_package_in_directory(
        &package,
        Path::new("/tmp/cpp_generation_test/geometry"),
    )?;

    Ok(())
}
