use super::r#type::Type;
use std::rc::Rc;

pub struct TypeRegistry {
    pub types: Vec<Rc<Type>>,
}

impl TypeRegistry {
    pub fn from_json(jvalue: &json::JsonValue) -> Option<Self> {
        let mut reg = Self { types: Vec::new() };
        let types: Vec<Option<Rc<Type>>> = match jvalue {
            json::JsonValue::Array(array) => {
                array.iter().map(|v| Type::from_json(&mut reg, v)).collect()
            }
            _ => return None,
        };

        let types: Vec<Rc<Type>> = types.into_iter().filter_map(|v| v).collect();

        return Some(Self { types });
    }

    pub fn get_type(&self, name: &str) -> Option<&Rc<Type>> {
        self.types.iter().find(|v| v.ty == name)
    }
}
