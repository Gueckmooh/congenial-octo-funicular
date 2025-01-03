use super::field::Field;
use super::type_registry::TypeRegistry;
use std::rc::Rc;

#[derive(Debug)]
pub struct Type {
    pub ty: String,
    pub named: bool,
    pub fields: Vec<Rc<Field>>,
}

impl Type {
    pub fn from_json(reg: &mut TypeRegistry, jvalue: &json::JsonValue) -> Option<Rc<Self>> {
        let value = match jvalue {
            json::JsonValue::Object(o) => o,
            _ => return None,
        };
        let r#type = match value.get("type") {
            Some(value) => value.as_str().unwrap_or(""),
            None => "",
        };
        let named = match value.get("named") {
            Some(value) => value.as_bool().unwrap_or(false),
            None => false,
        };
        let fields = match value.get("fields") {
            Some(json::JsonValue::Object(value)) => Some(value),
            _ => None,
        };
        let fields: Vec<Rc<Field>> = match fields {
            Some(fields) => fields
                .iter()
                .map(|(key, value)| Field::from_json(reg, value, String::from(key)))
                .filter(|v| v.is_some())
                .map(|v| v.unwrap())
                .collect(),
            None => Vec::new(),
        };

        let res = Self {
            ty: String::from(r#type),
            named,
            fields,
        };
        let res = Rc::new(res);

        Some(res)
    }
}
