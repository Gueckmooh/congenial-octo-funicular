use super::{Field, Type, Variable};

#[derive(Debug, Clone)]
pub struct Function {
    name: String,
    return_ty: Type,
    params: Vec<Variable>,
}

#[derive(Debug, Clone)]
pub struct Method {
    function: Function,
    attributes: MethodAttributes,
}

#[derive(Debug, Clone, Default)]
pub struct MethodAttributes {
    pub is_const: bool,
}

#[derive(Debug, Clone)]
pub enum SpecialMethod<'a> {
    Setter(Method, &'a Field),
    Getter(Method, &'a Field),
}

impl Function {
    #[must_use]
    pub fn new<S: Into<String>>(name: S, return_ty: Type, params: Vec<Variable>) -> Self {
        Self {
            name: name.into(),
            return_ty,
            params,
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
}

impl Method {
    #[must_use]
    pub fn new<S: Into<String>>(name: S, return_ty: Type, params: Vec<Variable>) -> Self {
        Self {
            function: Function::new(name, return_ty, params),
            attributes: MethodAttributes::default(),
        }
    }

    #[must_use]
    pub fn name(&self) -> &str {
        self.function.name()
    }

    #[must_use]
    pub fn return_ty(&self) -> &Type {
        self.function.return_ty()
    }

    #[must_use]
    pub fn params(&self) -> &[Variable] {
        self.function.params()
    }

    #[must_use]
    pub fn attributes(&self) -> &MethodAttributes {
        &self.attributes
    }
}
