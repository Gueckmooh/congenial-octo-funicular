use crate::{Type, Variable};

#[derive(Debug, Clone)]
pub struct Function {
    name: String,
    return_ty: Type,
    params: Vec<Variable>,
    attributes: Attributes,
}

#[derive(Debug, Clone, Default)]
pub struct Attributes {
    pub is_mutating: bool,
}

impl Function {
    #[must_use]
    pub fn new<S: Into<String>>(name: S, return_ty: Type, params: Vec<Variable>) -> Self {
        Self {
            name: name.into(),
            return_ty,
            params,
            attributes: Attributes::default(),
        }
    }

    #[must_use]
    pub fn name(&self) -> &str {
        &self.name
    }

    #[must_use]
    pub fn return_ty(&self) -> &Type {
        &self.return_ty
    }

    #[must_use]
    pub fn params(&self) -> &[Variable] {
        &self.params
    }

    #[must_use]
    pub fn attributes(&self) -> &Attributes {
        &self.attributes
    }

    #[must_use]
    pub fn as_mutating(self) -> Self {
        Self {
            attributes: Attributes { is_mutating: true },
            ..self
        }
    }
}
