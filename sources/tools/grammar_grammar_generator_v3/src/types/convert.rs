use std::collections::BTreeMap;

use super::*;
use crate::node_types::*;

use anyhow::{ensure, Result};
use convert_case::{Case, Casing};

pub fn convert_node_info(info: &NodeInfoJSON) -> Result<Struct> {
    println!("Converting: {:#?}", info);
    ensure!(
        info.named,
        "Could not generate struct from unnamed type info '{}'",
        info.kind,
    );
    let struct_name = info.kind.to_case(Case::Pascal);

    let mut fields = info
        .fields
        .as_ref()
        .unwrap_or(&BTreeMap::new())
        .iter()
        .map(|(k, v)| convert_field_info(k, v))
        .collect::<Result<Vec<_>>>()?;

    info.children
        .as_ref()
        .and_then(|v| convert_field_info("value", v).ok())
        .or_else(|| {
            fields
                .is_empty()
                .then(|| Variable::new("value", Type::String))
        })
        .and_then(|v| Some(fields.push(v)));

    let methods: Vec<Function> = fields.iter().map(generate_getter).collect();
    let methods: Vec<Function> = methods
        .into_iter()
        .chain(fields.iter().map(generate_setter))
        .collect();
    let methods: Vec<Function> = methods
        .into_iter()
        .chain(
            fields
                .iter()
                .filter(|v| v.ty.is_vector())
                .map(generate_add)
                .collect::<Result<Vec<_>>>()?
                .into_iter(),
        )
        .collect();

    let res = Struct::new(struct_name, fields, methods);
    Ok(res)
}

fn generate_getter(field: &Variable) -> Function {
    let mut f = Function::new(
        field.getter_name(),
        field.ty.clone().make_ref().make_qualified(true),
        vec![],
        vec![format!("return {};", field.var_name())],
    );
    f.set_is_const(true);
    f
}

fn generate_setter(field: &Variable) -> Function {
    Function::new(
        field.setter_name(),
        Type::Void,
        vec![Variable::new("value", field.ty.clone())],
        vec![format!("{} = std::move(value);", field.var_name())],
    )
}

fn generate_add(field: &Variable) -> Result<Function> {
    ensure!(
        field.ty.is_vector(),
        "Cannot generate add function on non vector field"
    );
    Ok(Function::new(
        field.anyer_name("add"),
        Type::Void,
        vec![Variable::new(
            "value",
            // @todo maybe not two clones in one line
            field
                .ty
                .clone()
                .try_into_vector()
                .map_err(anyhow::Error::from)?
                .as_ref()
                .clone(),
        )],
        vec![format!(
            "{}.emplace_back(std::move(value));",
            field.var_name()
        )],
    ))
}

fn convert_field_info<S: Into<String>>(name: S, info: &FieldInfoJSON) -> Result<Variable> {
    let types: Vec<_> = info.types.iter().filter(|v| v.named).collect();
    ensure!(!types.is_empty(), "Field {} has no type", name.into());
    let ty = if types.len() == 1 {
        convert_node_type(types.first().unwrap())?
    } else {
        let sub_types = types
            .into_iter()
            .map(convert_node_type)
            .collect::<Result<Vec<_>>>()?;
        Type::Variant(sub_types)
    };
    let ty = if info.multiple {
        Type::Vector(Box::new(ty))
    } else {
        ty
    };
    let ty = if !info.required && !ty.is_vector() {
        Type::Optional(Box::new(ty))
    } else {
        ty
    };
    Ok(Variable::new(name, ty))
}

fn convert_node_type(ty: &NodeTypeJSON) -> Result<Type> {
    ensure!(
        ty.named,
        "Could not generate type from unnamed type '{}'",
        ty.kind,
    );
    let struct_name = ty.kind.to_case(Case::Pascal);
    Ok(Type::Struct(struct_name))
}
