use super::{Field, Type, Variable};

#[derive(Debug, Clone)]
pub struct Function {
    name: String,
    return_ty: Type,
    params: Vec<Variable>,
    special_kind: Option<SpecialFunctionKind>,
}

#[derive(Debug, Clone)]
pub enum SpecialFunctionKind {
    Getter(Field),
    Setter(Field),
}

impl Function {
    #[must_use]
    pub fn new(
        name: String,
        return_ty: Type,
        params: Vec<Variable>,
        special_kind: Option<SpecialFunctionKind>,
    ) -> Self {
        Self {
            name,
            return_ty,
            params,
            special_kind,
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
    pub const fn is_special(&self) -> bool {
        self.special_kind.is_some()
    }

    #[must_use]
    pub const fn is_not_special(&self) -> bool {
        self.special_kind.is_none()
    }

    #[must_use]
    pub fn is_setter(&self) -> bool {
        self.special_kind
            .as_ref()
            .is_some_and(SpecialFunctionKind::is_setter)
    }

    #[must_use]
    pub fn is_getter(&self) -> bool {
        self.special_kind
            .as_ref()
            .is_some_and(SpecialFunctionKind::is_getter)
    }

    #[must_use]
    pub fn special_kind(&self) -> Option<&SpecialFunctionKind> {
        self.special_kind.as_ref()
    }
}

impl SpecialFunctionKind {
    /// Returns `true` if the special function kind is [`Getter`].
    ///
    /// [`Getter`]: SpecialFunctionKind::Getter
    #[must_use]
    pub fn is_getter(&self) -> bool {
        matches!(self, Self::Getter(..))
    }

    /// Returns `true` if the special function kind is [`Setter`].
    ///
    /// [`Setter`]: SpecialFunctionKind::Setter
    #[must_use]
    pub fn is_setter(&self) -> bool {
        matches!(self, Self::Setter(..))
    }

    #[must_use]
    pub fn as_getter(&self) -> Option<&Field> {
        if let Self::Getter(v) = self {
            Some(v)
        } else {
            None
        }
    }

    #[must_use]
    pub fn as_setter(&self) -> Option<&Field> {
        if let Self::Setter(v) = self {
            Some(v)
        } else {
            None
        }
    }

    /// # Errors
    ///
    /// This function will return an error if the function is not a getter.
    pub fn try_into_getter(self) -> Result<Field, Self> {
        if let Self::Getter(v) = self {
            Ok(v)
        } else {
            Err(self)
        }
    }

    /// # Errors
    ///
    /// This function will return an error if the function is not a setter.
    pub fn try_into_setter(self) -> Result<Field, Self> {
        if let Self::Setter(v) = self {
            Ok(v)
        } else {
            Err(self)
        }
    }
}
