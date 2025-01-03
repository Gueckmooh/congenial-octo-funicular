use std::rc::Rc;

use super::Element;

#[derive(Debug)]
pub struct Type {
    pub name: String,
    pub named: bool,
    pub fields: Vec<Rc<Element>>,
    pub children: Option<Rc<Element>>,
}

pub type TypePtr = Rc<Type>;

#[derive(Debug)]
pub enum TypeRef {
    Name(String),
    Type(TypePtr),
}

impl TypeRef {
    /// Returns `true` if the type ref is [`Name`].
    ///
    /// [`Name`]: TypeRef::Name
    #[must_use]
    pub fn is_name(&self) -> bool {
        matches!(self, Self::Name(..))
    }

    /// Returns `true` if the type ref is [`Type`].
    ///
    /// [`Type`]: TypeRef::Type
    #[must_use]
    pub fn is_type(&self) -> bool {
        matches!(self, Self::Type(..))
    }

    pub fn r#type(&self) -> Option<TypePtr> {
        match self {
            TypeRef::Type(t) => Some(t.clone()),
            _ => None,
        }
    }

    pub fn named_type(&self) -> Option<TypePtr> {
        match self {
            TypeRef::Type(t) => {
                if t.named {
                    Some(t.clone())
                } else {
                    None
                }
            }
            _ => None,
        }
    }

    pub fn get_name(&self) -> &String {
        match self {
            Self::Name(s) => &s,
            Self::Type(t) => &t.name,
        }
    }
}

impl Type {
    /// Creates a new [`Type`].
    pub fn new(
        name: String,
        named: bool,
        fields: Vec<Rc<Element>>,
        children: Option<Rc<Element>>,
    ) -> Self {
        Self {
            name,
            named,
            fields,
            children,
        }
    }

    pub fn maybe_from_json(jvalue: &json::JsonValue) -> Option<Rc<Self>> {
        let jobject = match jvalue {
            json::JsonValue::Object(o) => o,
            _ => return None,
        };

        let name = match jobject.get("type") {
            Some(value) => value.as_str().unwrap_or_default(),
            None => "",
        };

        let named = match jobject.get("named") {
            Some(value) => value.as_bool().unwrap_or_default(),
            None => false,
        };

        let fields = match jobject.get("fields") {
            Some(json::JsonValue::Object(object)) => object,
            _ => &json::object::Object::new(),
        };

        let fields = fields
            .iter()
            .filter_map(|(k, v)| Element::maybe_from_json(String::from(k), v))
            .collect();

        let children = match jobject.get("children") {
            Some(value) => Element::maybe_from_json(String::from(""), value),
            _ => None,
        };

        return Some(Rc::new(Type::new(
            String::from(name),
            named,
            fields,
            children,
        )));
    }
}
