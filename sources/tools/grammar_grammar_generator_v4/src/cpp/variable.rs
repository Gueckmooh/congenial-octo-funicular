use convert_case::{Case, Casing};

use super::{Method, SpecialMethod, Type};

#[derive(Debug, Clone)]
pub struct Variable {
    name: String,
    ty: Type,
}

#[derive(Debug, Clone)]
pub struct Field {
    variable: Variable,
}

impl Variable {
    #[must_use]
    pub fn new<S: Into<String>>(ty: Type, name: S) -> Self {
        Self {
            ty,
            name: name.into(),
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
}

impl Field {
    #[must_use]
    pub fn new<S: AsRef<str>>(ty: Type, name: S) -> Self {
        Self {
            variable: Variable::new(ty, name.as_ref()),
        }
    }

    #[must_use]
    pub fn name(&self) -> &str {
        self.variable.name()
    }

    #[must_use]
    pub fn ty(&self) -> &Type {
        self.variable.ty()
    }

    #[must_use]
    pub fn field_name(&self) -> String {
        format!("m_{}", self.name().to_case(Case::Camel))
    }

    #[must_use]
    pub fn getter_name(&self) -> String {
        format!("get{}", self.name().to_case(Case::Pascal))
    }

    #[must_use]
    pub fn setter_name(&self) -> String {
        format!("set{}", self.name().to_case(Case::Pascal))
    }

    #[must_use]
    pub fn getter(&self) -> SpecialMethod<'_> {
        SpecialMethod::Getter(
            Method::new(self.getter_name(), self.ty().as_const_reference(), vec![]),
            self,
        )
    }

    #[must_use]
    pub fn setter(&self) -> SpecialMethod<'_> {
        SpecialMethod::Setter(
            Method::new(
                self.setter_name(),
                Type::Void,
                vec![Variable::new(self.ty().clone(), self.name())],
            ),
            self,
        )
    }
}
