use std::rc::Rc;

use super::{Type, TypeRef};

#[derive(Debug)]
pub struct TypeRegistry {
    pub types: Vec<Rc<Type>>,
}

impl TypeRegistry {
    pub fn new(types: Vec<Rc<Type>>) -> Self {
        Self { types }
    }

    pub fn maybe_from_json(jvalue: &json::JsonValue) -> Option<Rc<Self>> {
        let jarray = match jvalue {
            json::JsonValue::Array(array) => array,
            _ => return None,
        };

        let types = jarray
            .into_iter()
            .filter_map(Type::maybe_from_json)
            .collect();

        return Some(Rc::new(TypeRegistry::new(types)));
    }

    pub fn lookup(&self, type_ref: &TypeRef) -> Option<Rc<Type>> {
        for ty in self.types.iter() {
            if &ty.name == type_ref.get_name() {
                return Some(ty.clone());
            }
        }
        None
    }
}
