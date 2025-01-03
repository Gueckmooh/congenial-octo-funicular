#[derive(Debug, Clone)]
pub enum Type {
    Void,
    String,
    Reference(Box<Type>),
    Qualified(Qualifiers, Box<Type>),
}

#[derive(Debug, Clone)]
pub struct Qualifiers {
    pub is_const: bool,
}

impl Type {
    #[must_use]
    pub fn as_reference(&self) -> Self {
        Self::Reference(Box::new(self.clone()))
    }

    #[must_use]
    pub fn as_const_reference(&self) -> Self {
        Self::Qualified(Qualifiers { is_const: true }, Box::new(self.as_reference()))
    }
}
