use super::r#type::Type;
use super::type_registry::TypeRegistry;
use std::rc::Rc;

#[derive(Debug)]
pub struct Field {
    pub name: String,
    pub multiple: bool,
    pub required: bool,
    pub types: Vec<Rc<Type>>,
}

impl Field {
    pub fn from_json(
        reg: &mut TypeRegistry,
        jvalue: &json::JsonValue,
        name: String,
    ) -> Option<Rc<Self>> {
        let value = match jvalue {
            json::JsonValue::Object(o) => o,
            _ => return None,
        };
        let multiple = value
            .get("multiple")
            .unwrap_or(&json::JsonValue::Null)
            .as_bool()
            .unwrap_or(false);
        let required = value
            .get("required")
            .unwrap_or(&json::JsonValue::Null)
            .as_bool()
            .unwrap_or(false);
        let types = value.get("types");
        let types = match types {
            Some(json::JsonValue::Array(array)) => array
                .iter()
                .map(|v| Type::from_json(reg, v))
                .filter_map(|v| v)
                .collect(),
            _ => Vec::new(),
        };
        types.iter().for_each(|v| println!("Adding type {:?}", v));
        types.iter().for_each(|t| reg.types.push(t.clone()));

        let res = Self {
            name,
            multiple,
            required,
            types,
        };
        let res = Rc::new(res);

        Some(res)
    }
}
