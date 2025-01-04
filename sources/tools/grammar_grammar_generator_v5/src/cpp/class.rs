use super::Field;

#[derive(Debug, Clone)]
pub struct Class {
    name: String,
    fields: Vec<Field>,
    is_struct: bool,
}

impl Class {
    pub fn new<S: Into<String>>(name: S, fields: Vec<Field>) -> Self {
        Self {
            name: name.into(),
            fields,
            is_struct: false,
        }
    }

    #[must_use]
    pub fn name(&self) -> &str {
        &self.name
    }

    #[must_use]
    pub fn fields(&self) -> &[Field] {
        &self.fields
    }

    #[must_use]
    pub fn is_struct(&self) -> bool {
        self.is_struct
    }

    pub fn set_is_struct(&mut self, is_struct: bool) {
        self.is_struct = is_struct;
    }
}
