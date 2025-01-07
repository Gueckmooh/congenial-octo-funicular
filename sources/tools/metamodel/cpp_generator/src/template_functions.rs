use std::collections::HashMap;

use convert_case::{Case, Casing};
use tera::{from_value, to_value};

use crate::cpp::Type;

fn field_name(params: &HashMap<String, tera::Value>) -> tera::Result<tera::Value> {
    match params.get("name") {
        Some(tera::Value::String(v)) => {
            Ok(tera::Value::String(format!("m_{}", v.to_case(Case::Camel))))
        }
        _ => Err("Wrong param".into()),
    }
}

fn getter_name(params: &HashMap<String, tera::Value>) -> tera::Result<tera::Value> {
    match params.get("name") {
        Some(tera::Value::String(v)) => Ok(tera::Value::String(format!(
            "get{}",
            v.to_case(Case::Pascal)
        ))),
        _ => Err("Wrong param".into()),
    }
}

fn setter_name(params: &HashMap<String, tera::Value>) -> tera::Result<tera::Value> {
    match params.get("name") {
        Some(tera::Value::String(v)) => Ok(tera::Value::String(format!(
            "set{}",
            v.to_case(Case::Pascal)
        ))),
        _ => Err("Wrong param".into()),
    }
}

fn type_str(params: &HashMap<String, tera::Value>) -> tera::Result<tera::Value> {
    match params.get("type") {
        Some(v) => match from_value::<Type>(v.clone()) {
            Ok(v) => Ok(tera::Value::String(v.into())),
            Err(_) => Err(format!("Cannot deserialize type: {v}").into()),
        },
        _ => Err("Wrong param".into()),
    }
}

fn type_view(params: &HashMap<String, tera::Value>) -> tera::Result<tera::Value> {
    match params.get("type") {
        Some(v) => match from_value::<Type>(v.clone()) {
            Ok(v) => Ok(to_value(v.make_view())?),
            Err(_) => Err(format!("Cannot deserialize type: {v}").into()),
        },
        _ => Err("Wrong param".into()),
    }
}

fn type_is_trivially_copyable(params: &HashMap<String, tera::Value>) -> tera::Result<tera::Value> {
    match params.get("type") {
        Some(v) => match from_value::<Type>(v.clone()) {
            Ok(v) => Ok(tera::Value::Bool(v.is_trivialy_copyable())),
            Err(_) => Err(format!("Cannot deserialize type: {v}").into()),
        },
        _ => Err("Wrong param".into()),
    }
}

fn include_file_for_type(params: &HashMap<String, tera::Value>) -> tera::Result<tera::Value> {
    match params.get("type") {
        Some(v) => match from_value::<Type>(v.clone()) {
            Ok(v) => match v {
                Type::Void => Err(format!("No include file for {v:?}").into()),
                Type::Int32 => Ok(tera::Value::String("<cstdint>".into())),
                Type::String => Ok(tera::Value::String("<string>".into())),
                Type::StringView => Ok(tera::Value::String("<string_view>".into())),
                Type::Object(o) => Ok(tera::Value::String(format!(
                    "\"{}.hpp\"",
                    o.to_case(Case::Snake)
                ))),
                Type::Ref(_) => Err(format!("No include file for {v:?}").into()),
                Type::Qualified(_, _) => Err(format!("No include file for {v:?}").into()),
            },
            Err(_) => Err(format!("Cannot deserialize type: {v}").into()),
        },
        _ => Err("Wrong param".into()),
    }
}

// fn print_body(params: &HashMap<String, tera::Value>) -> tera::Result<tera::Value> {
//     match params.get("class") {
//         Some(v) => match from_value::<cpp::Class>(v.clone()) {
//             Ok(v) => {
//                 let mut body = format!("")

//             }
//             Err(_) => Err(format!("Cannot deserialize type: {v}").into()),
//         },
//         _ => Err("Wrong param".into()),
//     }
// }

pub fn register_functions(tera: &mut tera::Tera) {
    tera.register_function("field_name", field_name);
    tera.register_function("getter_name", getter_name);
    tera.register_function("setter_name", setter_name);
    tera.register_function("type_str", type_str);
    tera.register_function("type_view", type_view);
    tera.register_function("type_is_trivially_copyable", type_is_trivially_copyable);
    tera.register_function("include_file_for_type", include_file_for_type);
}
