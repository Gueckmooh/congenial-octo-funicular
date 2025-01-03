#[derive(Debug, Clone)]
pub enum Type {
    Void,
    String,

    Reference(Box<Type>),
    Qualified(Qualifiers, Box<Type>),
}

#[derive(Debug, Clone, Default)]
pub struct Qualifiers {
    pub is_const: bool,
}

impl Type {
    /// Returns `true` if the type is [`Void`].
    ///
    /// [`Void`]: Type::Void
    #[must_use]
    pub fn is_void(&self) -> bool {
        matches!(self, Self::Void)
    }

    /// Returns `true` if the type is [`String`].
    ///
    /// [`String`]: Type::String
    #[must_use]
    pub fn is_string(&self) -> bool {
        matches!(self, Self::String)
    }

    /// Returns `true` if the type is [`Reference`].
    ///
    /// [`Reference`]: Type::Reference
    #[must_use]
    pub fn is_reference(&self) -> bool {
        matches!(self, Self::Reference(..))
    }

    /// Returns `true` if the type is [`Qualified`].
    ///
    /// [`Qualified`]: Type::Qualified
    #[must_use]
    pub fn is_qualified(&self) -> bool {
        matches!(self, Self::Qualified(..))
    }

    #[must_use]
    pub fn to_reference(self) -> Self {
        Self::Reference(Box::new(self))
    }

    #[must_use]
    pub fn to_const_reference(self) -> Self {
        Self::Qualified(Qualifiers { is_const: true }, Box::new(self.to_reference()))
    }
}
