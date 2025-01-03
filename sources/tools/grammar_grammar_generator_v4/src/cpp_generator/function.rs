use super::{CPPGenerator, Generate, GenerateVal};
use crate::cpp::{Field, Function, Method, SpecialMethod, Type, Variable};
use anyhow::{Error, Result};
use std::fmt::{Display, Write};

impl<W: Write> Generate<Function> for CPPGenerator<W> {
    fn generate(&mut self, value: &Function) -> Result<()> {
        self.generate_function(value.name(), value.return_ty(), value.params())
    }
}

impl<W: Write> Generate<Method> for CPPGenerator<W> {
    fn generate(&mut self, value: &Method) -> Result<()> {
        self.generate_function(value.name(), value.return_ty(), value.params())
    }
}

impl<W: Write> Generate<SpecialMethod<'_>> for CPPGenerator<W> {
    fn generate(&mut self, value: &SpecialMethod) -> Result<()> {
        match value {
            SpecialMethod::Setter(method, field) => self.generate_setter(method, field),
            SpecialMethod::Getter(method, field) => self.generate_getter(method, field),
        }
    }
}

impl<W: Write> CPPGenerator<W> {
    fn generate_function_signature<S: Display>(
        &mut self,
        name: S,
        return_ty: &Type,
        params: &[Variable],
    ) -> Result<()> {
        write!(
            self.w,
            "{} {name}({})",
            String::gen_str(return_ty)?,
            params
                .iter()
                .map(String::gen_str)
                .collect::<Result<Vec<String>>>()?
                .join(", ")
        )
        .map_err(Error::from)
    }
    fn generate_function<S: Display>(
        &mut self,
        name: S,
        return_ty: &Type,
        params: &[Variable],
    ) -> Result<()> {
        write!(self.w, "{}", self.indent())?;
        self.generate_function_signature(name, return_ty, params)
    }

    fn generate_getter(&mut self, method: &Method, field: &Field) -> Result<()> {
        write!(self.w, "{}", self.indent())?;
        self.generate_function_signature(method.name(), method.return_ty(), method.params())?;
        writeln!(self.w, " {{")?;
        self.update_indent(1)?;
        writeln!(self.w, "{}return {};", self.indent(), field.field_name())?;
        self.update_indent(-1)?;
        writeln!(self.w, "{}}}", self.indent()).map_err(Error::from)
    }

    fn generate_setter(&mut self, method: &Method, field: &Field) -> Result<()> {
        write!(self.w, "{}", self.indent())?;
        self.generate_function_signature(method.name(), method.return_ty(), method.params())?;
        writeln!(self.w, " {{")?;
        self.update_indent(1)?;
        writeln!(
            self.w,
            "{}{} = std::move({});",
            self.indent(),
            field.field_name(),
            field.name()
        )?;
        self.update_indent(-1)?;
        writeln!(self.w, "{}}}", self.indent()).map_err(Error::from)
    }
}
