use super::{CPPGenerator, Generate, GenerateVal};
use crate::cpp::Type;
use anyhow::{Error, Result};
use std::fmt::Write;

impl<W: Write> Generate<Type> for CPPGenerator<W> {
    fn generate(&mut self, value: &Type) -> Result<()> {
        match value {
            Type::Void => write!(self.w, "void"),
            Type::String => write!(self.w, "std::string"),
            Type::Reference(ty) => write!(self.w, "{}&", String::gen_str(ty.as_ref())?),
            Type::Qualified(qualifiers, ty) => {
                let is_const = qualifiers.is_const.then_some("const ").unwrap_or_default();
                write!(self.w, "{is_const}{}", String::gen_str(ty.as_ref())?)
            }
        }
        .map_err(Error::from)
    }
}
