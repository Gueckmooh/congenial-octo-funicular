use std::rc::Rc;

use crate::error::Error;

use super::{Type, TypeRef, TypeRegistry};

#[derive(Debug)]
pub struct Element {
    pub name: String,
    pub multiple: bool,
    pub required: bool,
    pub types: Vec<TypeRef>,
}

pub type ElementPtr = Rc<Element>;

impl Element {
    pub fn new(name: String, multiple: bool, required: bool, types: Vec<TypeRef>) -> Self {
        Self {
            name,
            multiple,
            required,
            types,
        }
    }

    pub fn maybe_from_json(name: String, jvalue: &json::JsonValue) -> Option<Rc<Self>> {
        let jobject = match jvalue {
            json::JsonValue::Object(o) => o,
            _ => return None,
        };

        let multiple = match jobject.get("multiple") {
            Some(value) => value.as_bool().unwrap_or_default(),
            None => false,
        };

        let required = match jobject.get("required") {
            Some(value) => value.as_bool().unwrap_or_default(),
            None => false,
        };

        let types = match jobject.get("types") {
            Some(json::JsonValue::Array(array)) => array,
            _ => &Vec::new(),
        };
        let types = types
            .into_iter()
            .filter_map(Type::maybe_from_json)
            .map(|v| TypeRef::Name(v.name.clone()))
            .collect();

        return Some(Rc::new(Element::new(name, multiple, required, types)));
    }

    pub fn lookup_type_refs(&self, registry: &TypeRegistry) -> Result<Self, Error> {
        let looked_up_types: Vec<TypeRef> = self
            .types
            .iter()
            .filter_map(|v| registry.lookup(v))
            .map(|v| TypeRef::Type(v))
            .collect();
        if looked_up_types.len() != self.types.len() {
            return Err(Error::TypeCheck {
                msg: String::from("caca"),
            });
        }

        Ok(Self {
            name: self.name.clone(),
            types: looked_up_types,
            ..*self
        })
    }
}
