use super::{CPPGenerator, Generate};
use crate::cpp::{Field, Type, Variable};
use anyhow::{Error, Result};
use std::fmt::{Display, Write};

impl<W: Write> Generate<Variable> for CPPGenerator<W> {
    fn generate(&mut self, value: &Variable) -> Result<()> {
        self.generate_variable(value.name(), value.ty())
    }
}

impl<W: Write> Generate<Field> for CPPGenerator<W> {
    fn generate(&mut self, value: &Field) -> Result<()> {
        self.generate_variable(value.field_name(), value.ty())
    }
}

impl<W: Write> CPPGenerator<W> {
    fn generate_variable<S: Display>(&mut self, name: S, ty: &Type) -> Result<()> {
        self.generate(ty)?;
        write!(self.w, " {name}").map_err(Error::from)
    }
}
