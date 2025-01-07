pub mod function;
mod generator_macros;
pub mod r#type;
pub mod variable;

use anyhow::Result;
use std::fmt::{Display, Write};

#[derive(Debug)]
pub struct Generator<W: Write> {
    pub(super) buffer: W,
    pub(super) indent_level: usize,
}

impl<W: Write + Default> Default for Generator<W> {
    fn default() -> Self {
        Self::new(W::default())
    }
}

impl<W: Write> Generator<W> {
    pub fn new(buffer: W) -> Self {
        Self {
            buffer,
            indent_level: 0,
        }
    }

    pub fn into_inner(self) -> W {
        self.buffer
    }
}

impl Display for Generator<String> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_str(&self.buffer)
    }
}

pub trait Generate<T> {
    /// Generates code from given value.
    ///
    /// # Errors
    ///
    /// This function will return an error if generation fails.
    fn generate(&mut self, value: &T) -> Result<()>;

    /// Generates a string from a default generator.
    ///
    /// # Errors
    ///
    /// This function will return an error if the generation fails.
    fn generate_str(value: &T) -> Result<String>
    where
        Self: Display + Default,
    {
        let mut gen = Self::default();
        gen.generate(value)?;
        Ok(format!("{gen}"))
    }
}

pub trait GenerateDecl<T> {
    /// Generates declaration from given value.
    ///
    /// # Errors
    ///
    /// This function will return an error if generation fails.
    fn generate_decl(&mut self, value: &T) -> Result<()>;
}
