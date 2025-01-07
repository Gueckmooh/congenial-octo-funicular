use crate::Type;

#[derive(Debug, Clone)]
pub struct Variable {
    name: String,
    ty: Type,
    attributes: Attributes,
}

#[derive(Debug, Clone, Default)]
pub struct Attributes {
    pub is_mutable: bool,
    pub is_field: bool,
}

impl Variable {
    #[must_use]
    pub fn new<S: Into<String>>(name: S, ty: Type) -> Self {
        Self {
            name: name.into(),
            ty,
            attributes: Attributes::default(),
        }
    }

    #[must_use]
    pub fn name(&self) -> &str {
        &self.name
    }

    #[must_use]
    pub fn ty(&self) -> &Type {
        &self.ty
    }

    #[must_use]
    pub fn attributes(&self) -> &Attributes {
        &self.attributes
    }

    #[must_use]
    pub fn as_mutable(self) -> Self {
        Self {
            attributes: Attributes {
                is_mutable: true,
                ..self.attributes
            },
            ..self
        }
    }

    #[must_use]
    pub fn with_name<S: Into<String>>(self, name: S) -> Self {
        Self {
            name: name.into(),
            ..self
        }
    }

    #[must_use]
    pub fn is_mutable(&self) -> bool {
        self.attributes().is_mutable
    }

    #[must_use]
    pub fn as_field(self) -> Variable {
        Self {
            attributes: Attributes {
                is_field: true,
                ..self.attributes
            },
            ..self
        }
    }
}
