use super::Field;

#[derive(Debug, Clone)]
pub struct Class {
    pub name: String,

    pub fields: Vec<Field>,
}

impl Class {
    pub fn new<S: Into<String>>(name: S, fields: Vec<Field>) -> Self {
        Self {
            name: name.into(),
            fields,
        }
    }
}
