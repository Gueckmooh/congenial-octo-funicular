pub mod class;
pub mod function;
pub mod r#type;
pub mod variable;

pub use class::*;
pub use function::*;
pub use r#type::*;
pub use variable::*;

#[derive(Debug, Clone)]
pub enum Visibility {
    Public,
    Protected,
    Private,
}

impl Visibility {
    /// Returns `true` if the visibility is [`Public`].
    ///
    /// [`Public`]: Visibility::Public
    #[must_use]
    pub fn is_public(&self) -> bool {
        matches!(self, Self::Public)
    }

    /// Returns `true` if the visibility is [`Protected`].
    ///
    /// [`Protected`]: Visibility::Protected
    #[must_use]
    pub fn is_protected(&self) -> bool {
        matches!(self, Self::Protected)
    }

    /// Returns `true` if the visibility is [`Private`].
    ///
    /// [`Private`]: Visibility::Private
    #[must_use]
    pub fn is_private(&self) -> bool {
        matches!(self, Self::Private)
    }
}
