use super::{CPPGenerator, Generate};
use crate::cpp::{Class, Field};
use anyhow::{Error, Result};
use std::fmt::Write;

impl<W: Write> Generate<Class> for CPPGenerator<W> {
    fn generate(&mut self, value: &Class) -> Result<()> {
        writeln!(self.w, "{}class {} {{", self.indent(), value.name)?;
        self.update_indent(1)?;

        writeln!(self.w, "{}public:", self.hindent())?;
        self.generate_fields_getters_and_setters(&value.fields)?;

        writeln!(self.w, "{}private:", self.hindent())?;
        self.generate_fields(&value.fields)?;

        self.update_indent(-1)?;
        writeln!(self.w, "{}}};", self.indent()).map_err(Error::from)
    }
}

impl<W: Write> CPPGenerator<W> {
    fn generate_field(&mut self, field: &Field) -> Result<()> {
        write!(self.w, "{}", self.indent())?;
        self.generate(field)?;
        writeln!(self.w, ";").map_err(Error::from)
    }

    fn generatre_field_getter(&mut self, field: &Field) -> Result<()> {
        self.generate(&field.getter())
    }

    fn generatre_field_setter(&mut self, field: &Field) -> Result<()> {
        self.generate(&field.setter())
    }

    fn generate_fields(&mut self, fields: &[Field]) -> Result<()> {
        fields.iter().try_for_each(|v| self.generate_field(v))
    }

    fn generate_fields_getters_and_setters(&mut self, fields: &[Field]) -> Result<()> {
        fields.iter().try_for_each(|v| {
            self.generatre_field_getter(v)
                .and_then(|_| self.generatre_field_setter(v))
        })
        // fields
        //     .iter()
        //     .try_for_each(|v| self.generatre_field_setter(v))
    }
}
