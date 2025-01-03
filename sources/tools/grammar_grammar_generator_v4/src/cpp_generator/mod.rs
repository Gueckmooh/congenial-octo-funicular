pub mod class;
pub mod function;
pub mod r#type;
pub mod variable;

use std::fmt::{Display, Write};

use anyhow::{bail, ensure, Result};

#[derive(Debug)]
pub struct CPPGenerator<W: Write> {
    w: W,
    indent: usize,
    style: CPPStyle,
}

#[derive(Debug)]
pub struct CPPStyle {
    indent_length: usize,
}

pub trait Generate<T> {
    /// Generate code for the given value.
    ///
    /// # Errors
    ///
    /// This function will return an error if an error occurs dring generation.
    fn generate(&mut self, value: &T) -> Result<()>;
}

pub trait GenerateVal<T> {
    fn must_gen_str(value: &T) -> Self;

    /// Generates a string from the given value.
    ///
    /// # Errors
    ///
    /// This function will return an error if the generation fails.
    fn gen_str(value: &T) -> Result<Self>
    where
        Self: Sized;
}

impl<T, W> GenerateVal<T> for W
where
    CPPGenerator<W>: Generate<T> + Default,
    W: Write + Default,
{
    fn must_gen_str(value: &T) -> Self {
        Self::gen_str(value).unwrap_or(Self::default())
    }

    fn gen_str(value: &T) -> Result<Self> {
        let mut gen = CPPGenerator::<W>::default();
        match gen.generate(value) {
            Ok(()) => Ok(gen.into_inner()),
            Err(e) => bail!(e),
        }
    }
}

impl Display for CPPGenerator<String> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.w)
    }
}

impl<W: Write> CPPGenerator<W> {
    /// Creates a new [`CPPGenerator<W>`].
    pub fn new(w: W, style: CPPStyle) -> Self {
        Self {
            w,
            indent: 0,
            style,
        }
    }

    /// Returns the inner writer value.
    pub fn into_inner(self) -> W {
        self.w
    }

    #[must_use]
    fn indent(&self) -> String {
        format!(
            "{:indent$}",
            "",
            indent = self.indent * self.style.indent_length
        )
    }

    #[must_use]
    fn hindent(&self) -> String {
        if self.indent == 0 {
            String::new()
        } else {
            format!(
                "{:indent$}",
                "",
                indent =
                    (self.indent - 1) * self.style.indent_length + (self.style.indent_length / 2)
            )
        }
    }

    /// Updates the indentation.
    ///
    /// # Errors
    ///
    /// This function will return an error if the new computed indentation is
    /// negative.
    fn update_indent(&mut self, value: isize) -> Result<()> {
        if value > 0 {
            self.indent += TryInto::<usize>::try_into(value)?;
        } else {
            ensure!(
                self.indent >= (-value).try_into()?,
                "Cannot decrement indentation below zero"
            );
            self.indent -= TryInto::<usize>::try_into(-value)?;
        }
        Ok(())
    }
}

impl Default for CPPGenerator<String> {
    fn default() -> Self {
        Self::new(String::new(), CPPStyle::default())
    }
}

impl Default for CPPStyle {
    fn default() -> Self {
        Self { indent_length: 4 }
    }
}
