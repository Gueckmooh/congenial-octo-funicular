use convert_case::{Case, Casing};

use super::{Function, SpecialFunctionKind, Type, Visibility};

#[derive(Debug, Clone)]
pub struct Variable {
    name: String,
    ty: Type,
}

#[derive(Debug, Clone)]
pub struct Field {
    variable: Variable,
    visibility: Visibility,
}

impl Variable {
    pub fn new<S: Into<String>>(name: S, ty: Type) -> Self {
        Self {
            name: name.into(),
            ty,
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
    pub fn new<S: Into<String>>(name: S, ty: Type, visibility: Visibility) -> Self {
        Self {
            variable: Variable::new(name, ty),
            visibility,
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
    pub fn visibility(&self) -> &Visibility {
        &self.visibility
    }

    #[must_use]
    pub fn is_public(&self) -> bool {
        self.visibility.is_public()
    }

    #[must_use]
    pub fn is_private(&self) -> bool {
        self.visibility.is_private()
    }

    #[must_use]
    pub fn is_protected(&self) -> bool {
        self.visibility.is_protected()
    }

    #[must_use]
    pub fn get_getter(&self) -> Function {
        let name = format!("get{}", self.name().to_case(Case::Pascal));
        Function::new(
            name,
            self.ty().clone().to_const_reference(),
            vec![],
            Some(SpecialFunctionKind::Getter(self.clone())),
        )
    }

    #[must_use]
    pub fn get_setter(&self) -> Function {
        let name = format!("set{}", self.name().to_case(Case::Pascal));
        Function::new(
            name,
            Type::Void,
            vec![Variable::new(self.name(), self.ty().clone())],
            Some(SpecialFunctionKind::Setter(self.clone())),
        )
    }
}
