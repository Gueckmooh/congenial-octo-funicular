use std::fmt::Write;

use anyhow::Result;

use crate::cpp::CPPGen;

use super::{Function, Struct, Variable};

pub trait GenCPP2 {
    fn gen_cpp<W: Write>(&self, gen: &mut CPPGen<W>) -> Result<()>;
}

impl GenCPP2 for Struct {
    fn gen_cpp<W: Write>(&self, gen: &mut CPPGen<W>) -> Result<()> {
        gen.open_class(&self.name)?;

        gen.public()?;
        self.methods
            .iter()
            .map(|v| v.gen_cpp(gen))
            .collect::<Result<Vec<()>>>()?;

        gen.private()?;
        self.fields
            .iter()
            .map(|v| v.gen_cpp(gen))
            .collect::<Result<Vec<()>>>()?;

        gen.close_class()?;
        Ok(())
    }
}

impl GenCPP2 for Variable {
    fn gen_cpp<W: Write>(&self, gen: &mut CPPGen<W>) -> Result<()> {
        gen.field(&self.ty, self.var_name())
    }
}

impl GenCPP2 for Function {
    fn gen_cpp<W: Write>(&self, gen: &mut CPPGen<W>) -> Result<()> {
        let attrs: Vec<String> = vec![self.is_const.then_some(String::from("const"))]
            .into_iter()
            .flatten()
            .collect();
        gen.open_function(
            &self.name,
            &self.return_ty,
            self.params
                .iter()
                .map(String::from)
                .collect::<Vec<String>>(),
            attrs,
        )?;
        self.body
            .iter()
            .map(|v| gen.write_line(v))
            .collect::<Result<Vec<()>>>()?;
        gen.close_function()
    }
}
